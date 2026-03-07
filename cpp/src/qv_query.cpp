#include "qv_query.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <string>

#include "qv_protocol.h"

namespace {
[[maybe_unused]] std::string env_or_empty(const char* key) {
    const char* value = std::getenv(key);
    if (value == nullptr) {
        return "";
    }
    return std::string(value);
}

[[maybe_unused]] std::string env_or_default(const char* key, const char* fallback) {
    const std::string value = env_or_empty(key);
    return value.empty() ? std::string(fallback) : value;
}

[[maybe_unused]] std::string trim(const std::string& input) {
    std::size_t start = 0;
    while (start < input.size() && std::isspace(static_cast<unsigned char>(input[start])) != 0) {
        ++start;
    }
    std::size_t end = input.size();
    while (end > start && std::isspace(static_cast<unsigned char>(input[end - 1])) != 0) {
        --end;
    }
    return input.substr(start, end - start);
}

[[maybe_unused]] std::string lower_ascii(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) {
        return static_cast<char>(std::tolower(c));
    });
    return value;
}

[[maybe_unused]] std::string upper_ascii(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) {
        return static_cast<char>(std::toupper(c));
    });
    return value;
}

[[maybe_unused]] std::string event_code_name(std::uint32_t code) {
    switch (code) {
        case CA_CONNECTED:
            return "CA_CONNECTED";
        case CA_DISCONNECTED:
            return "CA_DISCONNECTED";
        case CA_SOCKETERROR:
            return "CA_SOCKETERROR";
        case CA_RECEIVEDATA:
            return "CA_RECEIVEDATA";
        case CA_RECEIVESISE:
            return "CA_RECEIVESISE";
        case CA_RECEIVEMESSAGE:
            return "CA_RECEIVEMESSAGE";
        case CA_RECEIVECOMPLETE:
            return "CA_RECEIVECOMPLETE";
        case CA_RECEIVEERROR:
            return "CA_RECEIVEERROR";
        default:
            return "UNKNOWN_EVENT";
    }
}

[[maybe_unused]] std::string hex_preview(const char* data, int length, int limit = 32) {
    if (data == nullptr || length <= 0) {
        return "";
    }

    const int preview_len = std::min(length, limit);
    std::ostringstream oss;
    for (int i = 0; i < preview_len; ++i) {
        if (i > 0) {
            oss << ' ';
        }
        oss << std::uppercase << std::hex << std::setw(2) << std::setfill('0')
            << static_cast<int>(static_cast<unsigned char>(data[i]));
    }
    if (length > preview_len) {
        oss << " ...";
    }
    return oss.str();
}

std::string digits_only(const std::string& raw) {
    std::string out;
    out.reserve(raw.size());
    for (char c : raw) {
        if (std::isdigit(static_cast<unsigned char>(c)) != 0) {
            out.push_back(c);
        }
    }
    return out;
}

[[maybe_unused]] bool is_digit_4_password(const std::string& value) {
    if (value.size() != 4) {
        return false;
    }
    return std::all_of(value.begin(), value.end(), [](unsigned char c) {
        return std::isdigit(c) != 0;
    });
}

[[maybe_unused]] std::string normalize_order_no(const std::string& raw) {
    std::string digits = digits_only(raw);
    if (digits.empty()) {
        digits = "0";
    }
    if (digits.size() > 10) {
        digits = digits.substr(digits.size() - 10);
    }
    if (digits.size() < 10) {
        digits = std::string(10 - digits.size(), '0') + digits;
    }
    return digits;
}

[[maybe_unused]] std::string normalize_stock_code(const std::string& raw) {
    std::string out = digits_only(raw);
    if (out.size() > 6) {
        out = out.substr(out.size() - 6);
    }
    return out;
}

[[maybe_unused]] long long parse_number(const std::string& raw) {
    std::string cleaned = trim(raw);
    if (cleaned.empty()) {
        return 0;
    }

    cleaned.erase(std::remove(cleaned.begin(), cleaned.end(), ','), cleaned.end());

    try {
        double value = std::stod(cleaned);
        return static_cast<long long>(std::llround(value));
    } catch (...) {
        // fallback: keep only sign/digit
    }

    std::string filtered;
    filtered.reserve(cleaned.size());
    for (char c : cleaned) {
        if (std::isdigit(static_cast<unsigned char>(c)) != 0 || c == '-' || c == '+') {
            filtered.push_back(c);
        }
    }

    if (filtered.empty() || filtered == "-" || filtered == "+") {
        return 0;
    }

    try {
        return std::stoll(filtered);
    } catch (...) {
        return 0;
    }
}

[[maybe_unused]] std::string normalize_time(const std::string& raw) {
    std::string digits = digits_only(raw);
    if (digits.size() == 6) {
        return digits.substr(0, 2) + ":" + digits.substr(2, 2) + ":" + digits.substr(4, 2);
    }
    if (digits.size() == 8) {
        return digits.substr(0, 2) + ":" + digits.substr(2, 2) + ":" + digits.substr(4, 2);
    }
    return trim(raw);
}

[[maybe_unused]] long long derive_price_from_amount(long long qty, long long amount) {
    if (qty <= 0) {
        return 0;
    }
    if (amount <= 0) {
        return 0;
    }
    const double price = static_cast<double>(amount) / static_cast<double>(qty);
    return static_cast<long long>(std::llround(price));
}

[[maybe_unused]] std::string normalize_market_code(const std::string& raw, const std::string& fallback = "") {
    std::string code = upper_ascii(trim(raw));
    if (code == "KRX" || code == "NXT" || code == "SOR") {
        return code;
    }
    if (code.empty()) {
        return fallback;
    }
    return code;
}

bool is_retryable_failure(int attempt, int max_attempts) {
    return attempt + 1 < max_attempts;
}

std::string pad_order_no(long long value) {
    std::ostringstream oss;
    oss << std::setw(10) << std::setfill('0') << value;
    return oss.str();
}

#ifdef _WIN32
std::string cp949_to_utf8(const char* input, int length) {
    if (input == nullptr || length <= 0) {
        return "";
    }

    int wide_len = MultiByteToWideChar(949, 0, input, length, nullptr, 0);
    if (wide_len <= 0) {
        return std::string(input, input + length);
    }

    std::wstring wide;
    wide.resize(static_cast<std::size_t>(wide_len));
    MultiByteToWideChar(949, 0, input, length, wide.data(), wide_len);

    int utf8_len = WideCharToMultiByte(CP_UTF8, 0, wide.data(), wide_len, nullptr, 0, nullptr, nullptr);
    if (utf8_len <= 0) {
        return std::string(input, input + length);
    }

    std::string utf8;
    utf8.resize(static_cast<std::size_t>(utf8_len));
    WideCharToMultiByte(CP_UTF8, 0, wide.data(), wide_len, utf8.data(), utf8_len, nullptr, nullptr);
    return utf8;
}

template <std::size_t N>
std::string fixed_cp949_field(const char (&field)[N]) {
    int used = static_cast<int>(N);
    while (used > 0) {
        const char ch = field[used - 1];
        if (ch == '\0' || ch == ' ') {
            --used;
            continue;
        }
        break;
    }
    return trim(cp949_to_utf8(field, used));
}

std::string cstr_cp949(const char* field) {
    if (field == nullptr) {
        return "";
    }
    return trim(cp949_to_utf8(field, static_cast<int>(std::strlen(field))));
}

template <std::size_t N>
void set_fixed_field(char (&dst)[N], const std::string& value) {
    std::memset(dst, ' ', N);
    const std::size_t copy_len = std::min<std::size_t>(N, value.size());
    std::memcpy(dst, value.data(), copy_len);
}

struct Ts8180InBlock {
    char inq_gubunz1[1];
    char pswd_noz44[44];
    char group_noz4[4];
    char mkt_slctz1[1];
    char order_datez8[8];
    char issue_codez12[12];
    char comm_order_typez2[2];
    char conc_gubunz1[1];
    char inq_seq_gubunz1[1];
    char sort_gubunz1[1];
    char sell_buy_typez1[1];
    char mrgn_typez1[1];
    char accnt_admin_typez1[1];
    char order_noz10[10];
    char ctsz56[56];
    char trad_pswd1z44[44];
    char trad_pswd2z44[44];
    char IsPageUp[1];
};

struct Ts8180OutBlock1 {
    char order_datez8[8];
    char order_noz10[10];
    char orgnl_order_noz10[10];
    char accnt_noz11[11];
    char accnt_namez20[20];
    char order_kindz20[20];
    char trd_gubun_noz1[1];
    char trd_gubunz20[20];
    char trade_type_noz1[1];
    char trade_type1z20[20];
    char issue_codez12[12];
    char issue_namez40[40];
    char order_qtyz10[10];
    char conc_qtyz10[10];
    char order_unit_pricez12[12];
    char conc_unit_pricez12[12];
    char crctn_canc_qtyz10[10];
    char cfirm_qtyz10[10];
    char media_namez12[12];
    char proc_emp_noz5[5];
    char proc_timez8[8];
    char proc_termz8[8];
    char proc_typez12[12];
    char rejec_codez5[5];
    char avail_qtyz10[10];
    char mkt_typez1[1];
    char shsll_typez20[20];
    char passwd_noz8[8];
    char new_order_no1z10[10];
    char new_order_no2z10[10];
    char sor_order_noz10[10];
    char req_mkt_codez3[3];
    char send_mkt_codez3[3];
    char sor_split_ynz1[1];
    char stop_cond_pricez15_3[15];
    char reject_qtyz18[18];
    char req_mkt_namez50[50];
    char stop_reached_ynz1[1];
    char cancel_qtyz8[8];
};

struct Ts8180OutBlockIN {
    char ctsz56[56];
    char nextbutton[1];
};

struct Ts8118InBlock {
    char order_datez8[8];
    char order_noz10[10];
    char trad_pswd1z44[44];
    char trad_pswd2z44[44];
};

struct Ts8118OutBlock {
    char order_datez8[8];
    char order_noz10[10];
    char orgnl_order_noz10[10];
    char issue_codez6[6];
    char issue_namez20[20];
    char order_namez10[10];
    char trade_namez10[10];
    char order_qtyz10[10];
    char order_pricez9[9];
    char conc_qtyz10[10];
    char conc_amtz15[15];
    char avail_qtyz10[10];
    char proc_namez10[10];
    char reject_codez4[4];
    char media_namez10[10];
    char reject_qtyz10[10];
    char parent_child_typez8[8];
    char stop_pricez11[11];
    char sor_typez1[1];
    char req_mkt_codez3[3];
    char split_order_ynz1[1];
    char send_mkt_codez3[3];
    char exch_reject_codez4[4];
    char alt_exch_reject_codez4[4];
    char cancel_qtyz10[10];
};

static_assert(sizeof(Ts8180InBlock) == 233, "Ts8180InBlock size mismatch");
static_assert(sizeof(Ts8180OutBlock1) == 455, "Ts8180OutBlock1 size mismatch");
static_assert(sizeof(Ts8180OutBlockIN) == 57, "Ts8180OutBlockIN size mismatch");
static_assert(sizeof(Ts8118InBlock) == 106, "Ts8118InBlock size mismatch");
static_assert(sizeof(Ts8118OutBlock) == 207, "Ts8118OutBlock size mismatch");

std::string map_s8180_market(const Ts8180OutBlock1& row) {
    const std::string req = normalize_market_code(fixed_cp949_field(row.req_mkt_codez3));
    const std::string send = normalize_market_code(fixed_cp949_field(row.send_mkt_codez3));
    if (!req.empty()) {
        return req;
    }
    if (!send.empty()) {
        return send;
    }

    const std::string media = upper_ascii(fixed_cp949_field(row.media_namez12));
    if (media.find("NXT") != std::string::npos) {
        return "NXT";
    }
    if (media.find("KRX") != std::string::npos) {
        return "KRX";
    }
    if (media.find("SOR") != std::string::npos) {
        return "SOR";
    }
    return "KRX";
}
#endif
}  // namespace

QVQuery::QVQuery(QVAuth& auth, Logger& logger) : auth_(auth), logger_(logger) {
#ifdef _WIN32
    logger_.info(
        "TR struct sizes s8180_in=" + std::to_string(sizeof(Ts8180InBlock)) +
        " s8180_out1=" + std::to_string(sizeof(Ts8180OutBlock1)) +
        " s8180_paging=" + std::to_string(sizeof(Ts8180OutBlockIN)) +
        " s8118_in=" + std::to_string(sizeof(Ts8118InBlock)) +
        " s8118_out=" + std::to_string(sizeof(Ts8118OutBlock)));
#endif
}

bool QVQuery::fetch_executions(const std::string& trade_date,
                               std::vector<ExecutionRecord>& out,
                               std::vector<std::string>& warnings) {
    constexpr int kMaxAttempts = 3;
    std::string cts;
    bool has_more = true;
    bool page_up = false;

    while (has_more) {
        bool page_success = false;
        std::vector<ExecutionRecord> page_records;
        std::string next_cts;
        bool next_has_more = false;
        bool fatal_error = false;
        std::string page_error;

        for (int attempt = 0; attempt < kMaxAttempts; ++attempt) {
            page_records.clear();
            next_cts.clear();
            next_has_more = false;
            fatal_error = false;
            page_error.clear();

            if (fetch_s8180_page(trade_date, cts, page_up, page_records, next_cts, next_has_more, fatal_error, page_error)) {
                page_success = true;
                break;
            }

            logger_.warn("s8180 page fetch failed. attempt=" + std::to_string(attempt + 1));
            if (fatal_error) {
                logger_.error("s8180 page fetch failed with fatal error. no retry.");
                if (!page_error.empty()) {
                    warnings.push_back(page_error);
                }
                return false;
            }
            if (!is_retryable_failure(attempt, kMaxAttempts)) {
                if (!page_error.empty()) {
                    warnings.push_back(page_error);
                }
                return false;
            }
        }

        if (!page_success) {
            if (!page_error.empty()) {
                warnings.push_back(page_error);
            }
            return false;
        }

        for (auto& exec : page_records) {
            if (exec.exec_qty <= 0) {
                continue;
            }

            if (upper_ascii(exec.sor_split) == "Y") {
                std::vector<SplitDetail> details;
                if (fetch_s8118_details(trade_date, exec.order_no, details) && !details.empty()) {
                    for (auto& detail : details) {
                        if (detail.exec_time.empty()) {
                            detail.exec_time = exec.exec_time;
                        }
                        if (detail.market.empty()) {
                            detail.market = exec.market_code;
                        }
                        if (detail.exec_amount <= 0 && detail.exec_qty > 0 && detail.exec_price > 0) {
                            detail.exec_amount = detail.exec_qty * detail.exec_price;
                        }
                    }
                    exec.split_details = details;
                } else {
                    warnings.push_back("s8118 fallback applied for order_no=" + exec.order_no);
                }
            }

            if (exec.split_details.empty()) {
                SplitDetail fallback;
                fallback.exec_qty = exec.exec_qty;
                fallback.exec_price = exec.exec_avg_price;
                fallback.exec_amount = exec.exec_qty * exec.exec_avg_price;
                fallback.exec_time = exec.exec_time;
                fallback.market = exec.market_code;
                exec.split_details.push_back(fallback);
            }

            out.push_back(exec);
        }

        cts = next_cts;
        has_more = next_has_more;
        page_up = has_more;
    }

    return true;
}

bool QVQuery::fetch_s8180_page(const std::string& trade_date,
                               const std::string& cts,
                               bool is_page_up,
                               std::vector<ExecutionRecord>& page_out,
                               std::string& next_cts,
                               bool& has_more,
                               bool& fatal_error,
                               std::string& page_error) {
    if (auth_.is_mock_mode()) {
        (void)page_error;
        return fill_mock_s8180(trade_date, cts, page_out, next_cts, has_more);
    }

#ifndef _WIN32
    (void)trade_date;
    (void)cts;
    (void)is_page_up;
    (void)page_out;
    (void)next_cts;
    (void)has_more;
    (void)fatal_error;
    logger_.error("QV query is supported only on Windows.");
    return false;
#else
    page_out.clear();
    next_cts.clear();
    has_more = false;
    fatal_error = false;
    page_error.clear();

    const std::string tr_code = env_or_default("QV_EXEC_TR_CODE", "s8180");
    const int tr_index = next_exec_tr_index_++;
    auth_.discard_stale_query_events("before s8180 tr_index=" + std::to_string(tr_index));

    Ts8180InBlock input{};
    set_fixed_field(input.inq_gubunz1, env_or_default("QV_INQ_GUBUN", "3"));
    const std::string account_password =
        auth_.account_password().empty() ? env_or_empty("QV_ACCOUNT_PASSWORD") : auth_.account_password();
    logger_.info(
        "s8180 password validation account_index=" + std::to_string(auth_.account_index()) +
        " account_no=" + auth_.account_no() +
        " password_length=" + std::to_string(account_password.size()) +
        " is_digit_4=" + std::string(is_digit_4_password(account_password) ? "Y" : "N"));
    set_fixed_field(input.pswd_noz44, account_password);
    set_fixed_field(input.group_noz4, env_or_default("QV_GROUP_NO", "0000"));
    set_fixed_field(input.mkt_slctz1, env_or_default("QV_MKT_SLCT", "0"));
    set_fixed_field(input.order_datez8, trade_date);
    set_fixed_field(input.issue_codez12, env_or_empty("QV_ISSUE_CODE"));
    set_fixed_field(input.comm_order_typez2, env_or_default("QV_MEDIA_GUBUN", "CC"));
    set_fixed_field(input.conc_gubunz1, env_or_default("QV_CONC_GUBUN", "2"));
    set_fixed_field(input.inq_seq_gubunz1, env_or_default("QV_INQ_SEQ", "0"));
    set_fixed_field(input.sort_gubunz1, env_or_default("QV_SORT_GUBUN", "0"));
    set_fixed_field(input.sell_buy_typez1, env_or_default("QV_SELL_BUY", "0"));
    set_fixed_field(input.mrgn_typez1, env_or_default("QV_MRGN_TYPE", "0"));
    set_fixed_field(input.accnt_admin_typez1, env_or_default("QV_ACCNT_ADMIN", "0"));
    set_fixed_field(input.order_noz10, env_or_empty("QV_ORDER_NO"));
    set_fixed_field(input.ctsz56, cts);
    set_fixed_field(input.trad_pswd1z44, env_or_empty("QV_TRADE_PASSWORD1"));
    set_fixed_field(input.trad_pswd2z44, env_or_empty("QV_TRADE_PASSWORD2"));
    set_fixed_field(input.IsPageUp, is_page_up ? "N" : "");

    logger_.info(
        "Submitting s8180 tr_index=" + std::to_string(tr_index) +
        " trade_date=" + trade_date +
        " cts=" + (cts.empty() ? std::string("<empty>") : cts) +
        " is_page_up=" + std::string(is_page_up ? "Y" : "N"));

    if (!auth_.submit_query(tr_index, tr_code, &input, static_cast<int>(sizeof(input)))) {
        logger_.error("submit_query failed for tr=" + tr_code);
        return false;
    }

    const int timeout_ms = [] {
        try {
            return std::stoi(env_or_default("QV_QUERY_TIMEOUT_MS", "15000"));
        } catch (...) {
            return 15000;
        }
    }();

    const auto start = std::chrono::steady_clock::now();

    while (true) {
        const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - start);
        if (elapsed.count() >= timeout_ms) {
            logger_.error("s8180 query timeout");
            page_error = "TR 조회 타임아웃";
            auth_.drain_events_for_tr(tr_index, 500, "s8180 timeout");
            return false;
        }

        QVEvent event;
        std::string wait_error;
        if (!auth_.wait_for_event(event, 500, wait_error)) {
            if (wait_error.rfind("timeout", 0) == 0) {
                continue;
            }
            logger_.error("wait_for_event failed: " + wait_error);
            page_error = "이벤트 대기 실패";
            auth_.drain_events_for_tr(tr_index, 500, "s8180 wait_for_event failed");
            return false;
        }

        logger_.info(
            "s8180 event tr_index=" + std::to_string(event.tr_index) +
            " code=" + event_code_name(event.code) +
            " block_name=" + (event.block_name.empty() ? std::string("<empty>") : event.block_name) +
            " data_len=" + std::to_string(event.data_len));

        if (event.code == CA_RECEIVEMESSAGE) {
            if (event.tr_index == tr_index && !event.data.empty() &&
                event.data_len >= static_cast<int>(sizeof(MessageHeader))) {
                const auto* header = reinterpret_cast<const MessageHeader*>(event.data.data());
                const std::string code = trim(cp949_to_utf8(header->message_code, static_cast<int>(sizeof(header->message_code))));
                const std::string msg = trim(cp949_to_utf8(header->message, static_cast<int>(sizeof(header->message))));
                logger_.info("s8180 message [" + code + "] " + msg);
                if (code == "10009" || code == "21263" || msg.find("계좌비밀번호") != std::string::npos) {
                    logger_.error("s8180 account password rejected: " + msg);
                    fatal_error = true;
                    page_error = "계좌 비밀번호 오류";
                    auth_.drain_events_for_tr(tr_index, 1000, "s8180 account password rejected");
                    return false;
                }
            }
            continue;
        }

        if (event.code == CA_RECEIVEERROR) {
            if (event.tr_index == tr_index && !event.data.empty()) {
                logger_.error("s8180 error: " + cstr_cp949(event.data.data()));
            } else {
                logger_.error("s8180 receive error");
            }
            fatal_error = true;
            if (page_error.empty()) {
                page_error = "TR 수신 오류";
            }
            auth_.drain_events_for_tr(tr_index, 1000, "s8180 receive error");
            return false;
        }

        if (event.code == CA_RECEIVEDATA) {
            if (event.tr_index != tr_index || event.data.empty()) {
                continue;
            }

            const std::string block_name = lower_ascii(event.block_name);
            const char* payload = event.data.data();
            const int payload_len = event.data_len;

            logger_.info(
                "s8180 received data block_name=" + (block_name.empty() ? std::string("<empty>") : block_name) +
                " payload_len=" + std::to_string(payload_len));

            if (block_name.find("outblock1") != std::string::npos) {
                const int row_size = static_cast<int>(sizeof(Ts8180OutBlock1));
                if (payload_len < row_size) {
                    logger_.warn(
                        "s8180 outblock1 too short payload_len=" + std::to_string(payload_len) +
                        " row_size=" + std::to_string(row_size));
                    continue;
                }
                if (payload_len % row_size != 0) {
                    logger_.warn("s8180 outblock1 length is not aligned: " + std::to_string(payload_len));
                }

                const int count = payload_len / row_size;
                logger_.info(
                    "s8180 parsing outblock1 count=" + std::to_string(count) +
                    " row_size=" + std::to_string(row_size));
                const auto* rows = reinterpret_cast<const Ts8180OutBlock1*>(payload);
                for (int i = 0; i < count; ++i) {
                    const Ts8180OutBlock1& row = rows[i];
                    ExecutionRecord exec;
                    exec.account_no = auth_.account_no();
                    exec.order_no = normalize_order_no(fixed_cp949_field(row.order_noz10));
                    exec.orig_order_no = normalize_order_no(fixed_cp949_field(row.orgnl_order_noz10));
                    exec.order_type = fixed_cp949_field(row.order_kindz20);
                    exec.stock_code = normalize_stock_code(fixed_cp949_field(row.issue_codez12));
                    exec.stock_name = fixed_cp949_field(row.issue_namez40);
                    exec.order_qty = parse_number(fixed_cp949_field(row.order_qtyz10));
                    exec.exec_qty = parse_number(fixed_cp949_field(row.conc_qtyz10));
                    exec.order_price = parse_number(fixed_cp949_field(row.order_unit_pricez12));
                    exec.exec_avg_price = parse_number(fixed_cp949_field(row.conc_unit_pricez12));
                    exec.exec_time = normalize_time(fixed_cp949_field(row.proc_timez8));
                    exec.market_code = map_s8180_market(row);
                    exec.sor_split = upper_ascii(fixed_cp949_field(row.sor_split_ynz1));
                    if (exec.sor_split.empty()) {
                        exec.sor_split = "N";
                    }

                    if (exec.exec_qty > 0) {
                        logger_.info(
                            "s8180 row accepted order_no=" + exec.order_no +
                            " order_type=" + exec.order_type +
                            " stock=" + exec.stock_code +
                            " exec_qty=" + std::to_string(exec.exec_qty) +
                            " exec_avg_price=" + std::to_string(exec.exec_avg_price));
                        page_out.push_back(exec);
                    } else {
                        logger_.warn(
                            "s8180 row skipped order_no=" + exec.order_no +
                            " order_type=" + exec.order_type +
                            " stock=" + exec.stock_code +
                            " order_qty=" + std::to_string(exec.order_qty) +
                            " exec_qty=" + std::to_string(exec.exec_qty) +
                            " exec_avg_price=" + std::to_string(exec.exec_avg_price));
                    }
                }
                continue;
            }

            if (block_name.find("outblock_in") != std::string::npos ||
                block_name.find("outblock2") != std::string::npos ||
                block_name.find("outblock3") != std::string::npos) {
                if (payload_len >= static_cast<int>(sizeof(Ts8180OutBlockIN))) {
                    const auto* block = reinterpret_cast<const Ts8180OutBlockIN*>(payload);
                    next_cts = trim(cp949_to_utf8(block->ctsz56, static_cast<int>(sizeof(block->ctsz56))));
                    const std::string next = trim(cp949_to_utf8(block->nextbutton, static_cast<int>(sizeof(block->nextbutton))));
                    has_more = !next.empty();
                    logger_.info(
                        "s8180 paging block parsed block_name=" + block_name +
                        " next_cts=" + (next_cts.empty() ? std::string("<empty>") : next_cts) +
                        " nextbutton=" + (next.empty() ? std::string("<empty>") : next) +
                        " has_more=" + std::string(has_more ? "Y" : "N"));
                } else {
                    logger_.warn(
                        "s8180 paging block too short block_name=" + block_name +
                        " payload_len=" + std::to_string(payload_len));
                }
                continue;
            }

            logger_.warn(
                "s8180 unhandled data block block_name=" + (block_name.empty() ? std::string("<empty>") : block_name) +
                " payload_len=" + std::to_string(payload_len) +
                " payload_preview=" + hex_preview(payload, payload_len));
        }

        if (event.code == CA_RECEIVECOMPLETE) {
            if (event.tr_index == tr_index) {
                logger_.info(
                    "s8180 receive complete page_records=" + std::to_string(page_out.size()) +
                    " next_cts=" + (next_cts.empty() ? std::string("<empty>") : next_cts) +
                    " has_more=" + std::string(has_more ? "Y" : "N"));
                if (page_out.empty()) {
                    logger_.warn("s8180 completed with zero parsed executions for this page");
                }
                return true;
            }
        }
    }
#endif
}

bool QVQuery::fetch_s8118_details(const std::string& trade_date,
                                  const std::string& order_no,
                                  std::vector<SplitDetail>& details) {
    if (auth_.is_mock_mode()) {
        return fill_mock_s8118(order_no, details);
    }

#ifndef _WIN32
    (void)trade_date;
    (void)order_no;
    details.clear();
    logger_.warn("s8118 query is supported only on Windows.");
    return false;
#else
    details.clear();

    const std::string tr_code = env_or_default("QV_SPLIT_TR_CODE", "s8118");
    const int tr_index = next_split_tr_index_++;
    auth_.discard_stale_query_events("before s8118 tr_index=" + std::to_string(tr_index));

    Ts8118InBlock input{};
    set_fixed_field(input.order_datez8, trade_date);
    set_fixed_field(input.order_noz10, normalize_order_no(order_no));
    set_fixed_field(input.trad_pswd1z44, env_or_empty("QV_TRADE_PASSWORD1"));
    set_fixed_field(input.trad_pswd2z44, env_or_empty("QV_TRADE_PASSWORD2"));

    logger_.info(
        "Submitting s8118 tr_index=" + std::to_string(tr_index) +
        " trade_date=" + trade_date +
        " order_no=" + normalize_order_no(order_no));

    if (!auth_.submit_query(tr_index, tr_code, &input, static_cast<int>(sizeof(input)))) {
        logger_.warn("submit_query failed for s8118 order_no=" + order_no);
        return false;
    }

    const int timeout_ms = [] {
        try {
            return std::stoi(env_or_default("QV_QUERY_TIMEOUT_MS", "15000"));
        } catch (...) {
            return 15000;
        }
    }();

    const auto start = std::chrono::steady_clock::now();

    while (true) {
        const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - start);
        if (elapsed.count() >= timeout_ms) {
            logger_.warn("s8118 timeout for order_no=" + order_no);
            auth_.drain_events_for_tr(tr_index, 500, "s8118 timeout");
            return false;
        }

        QVEvent event;
        std::string wait_error;
        if (!auth_.wait_for_event(event, 500, wait_error)) {
            if (wait_error.rfind("timeout", 0) == 0) {
                continue;
            }
            logger_.warn("s8118 wait_for_event failed: " + wait_error);
            auth_.drain_events_for_tr(tr_index, 500, "s8118 wait_for_event failed");
            return false;
        }

        logger_.info(
            "s8118 event tr_index=" + std::to_string(event.tr_index) +
            " code=" + event_code_name(event.code) +
            " block_name=" + (event.block_name.empty() ? std::string("<empty>") : event.block_name) +
            " data_len=" + std::to_string(event.data_len));

        if (event.code == CA_RECEIVEMESSAGE) {
            if (event.tr_index == tr_index && !event.data.empty() &&
                event.data_len >= static_cast<int>(sizeof(MessageHeader))) {
                const auto* header = reinterpret_cast<const MessageHeader*>(event.data.data());
                const std::string code = trim(cp949_to_utf8(header->message_code, static_cast<int>(sizeof(header->message_code))));
                const std::string msg = trim(cp949_to_utf8(header->message, static_cast<int>(sizeof(header->message))));
                logger_.info("s8118 message [" + code + "] " + msg);
            }
            continue;
        }

        if (event.code == CA_RECEIVEERROR) {
            if (event.tr_index == tr_index && !event.data.empty()) {
                logger_.warn("s8118 error: " + cstr_cp949(event.data.data()));
            }
            auth_.drain_events_for_tr(tr_index, 500, "s8118 receive error");
            return false;
        }

        if (event.code == CA_RECEIVEDATA) {
            if (event.tr_index != tr_index || event.data.empty()) {
                continue;
            }

            const std::string block_name = lower_ascii(event.block_name);
            logger_.info(
                "s8118 received data block_name=" + (block_name.empty() ? std::string("<empty>") : block_name) +
                " payload_len=" + std::to_string(event.data_len));
            if (block_name.find("outblock") == std::string::npos || block_name.find("outblock_in") != std::string::npos) {
                logger_.warn("s8118 ignored data block block_name=" + block_name);
                continue;
            }

            const int row_size = static_cast<int>(sizeof(Ts8118OutBlock));
            if (event.data_len < row_size) {
                logger_.warn(
                    "s8118 payload shorter than row size payload_len=" + std::to_string(event.data_len) +
                    " row_size=" + std::to_string(row_size));
                continue;
            }

            const int count = event.data_len / row_size;
            logger_.info(
                "s8118 parsing outblock count=" + std::to_string(count) +
                " row_size=" + std::to_string(row_size));
            const auto* rows = reinterpret_cast<const Ts8118OutBlock*>(event.data.data());
            for (int i = 0; i < count; ++i) {
                const Ts8118OutBlock& row = rows[i];
                SplitDetail detail;
                detail.exec_qty = parse_number(fixed_cp949_field(row.conc_qtyz10));
                detail.exec_amount = parse_number(fixed_cp949_field(row.conc_amtz15));
                detail.exec_price = derive_price_from_amount(detail.exec_qty, detail.exec_amount);
                detail.market = normalize_market_code(
                    fixed_cp949_field(row.send_mkt_codez3),
                    normalize_market_code(fixed_cp949_field(row.req_mkt_codez3), "KRX"));
                detail.exec_time = "";

                if (detail.exec_qty > 0) {
                    logger_.info(
                        "s8118 row accepted order_no=" + normalize_order_no(order_no) +
                        " exec_qty=" + std::to_string(detail.exec_qty) +
                        " exec_amount=" + std::to_string(detail.exec_amount) +
                        " exec_price=" + std::to_string(detail.exec_price) +
                        " market=" + detail.market);
                    details.push_back(detail);
                } else {
                    logger_.warn(
                        "s8118 row skipped order_no=" + normalize_order_no(order_no) +
                        " exec_qty=" + std::to_string(detail.exec_qty) +
                        " exec_amount=" + std::to_string(detail.exec_amount));
                }
            }
            continue;
        }

        if (event.code == CA_RECEIVECOMPLETE) {
            if (event.tr_index == tr_index) {
                logger_.info(
                    "s8118 receive complete order_no=" + normalize_order_no(order_no) +
                    " detail_count=" + std::to_string(details.size()));
                return !details.empty();
            }
        }
    }
#endif
}

bool QVQuery::fill_mock_s8180(const std::string& trade_date,
                              const std::string& cts,
                              std::vector<ExecutionRecord>& page_out,
                              std::string& next_cts,
                              bool& has_more) {
    page_out.clear();

    if (cts.empty()) {
        ExecutionRecord e1;
        e1.account_no = auth_.account_no();
        e1.order_no = pad_order_no(1);
        e1.orig_order_no = pad_order_no(0);
        e1.order_type = "현금매수";
        e1.stock_code = "005930";
        e1.stock_name = "삼성전자";
        e1.order_qty = 100;
        e1.exec_qty = 100;
        e1.order_price = 71500;
        e1.exec_avg_price = 71546;
        e1.exec_time = "09:31:05";
        e1.market_code = "SOR";
        e1.sor_split = "Y";
        page_out.push_back(e1);

        next_cts = "PAGE2";
        has_more = true;
        logger_.info("Mock s8180 page 1 for " + trade_date);
        return true;
    }

    if (cts == "PAGE2") {
        ExecutionRecord e2;
        e2.account_no = auth_.account_no();
        e2.order_no = pad_order_no(2);
        e2.orig_order_no = pad_order_no(0);
        e2.order_type = "현금매도";
        e2.stock_code = "000660";
        e2.stock_name = "SK하이닉스";
        e2.order_qty = 50;
        e2.exec_qty = 50;
        e2.order_price = 82300;
        e2.exec_avg_price = 82300;
        e2.exec_time = "10:15:00";
        e2.market_code = "KRX";
        e2.sor_split = "N";

        SplitDetail d;
        d.exec_qty = 50;
        d.exec_price = 82300;
        d.exec_amount = 4115000;
        d.exec_time = "10:15:00";
        d.market = "KRX";
        e2.split_details.push_back(d);

        page_out.push_back(e2);

        next_cts.clear();
        has_more = false;
        logger_.info("Mock s8180 page 2 for " + trade_date);
        return true;
    }

    has_more = false;
    next_cts.clear();
    return true;
}

bool QVQuery::fill_mock_s8118(const std::string& order_no,
                              std::vector<SplitDetail>& details) {
    details.clear();

    if (order_no != "0000000001") {
        return false;
    }

    details.push_back(SplitDetail{37, 2645500, 71500, "09:31:02", "KRX"});
    details.push_back(SplitDetail{7, 501200, 71600, "09:31:02", "NXT"});
    details.push_back(SplitDetail{56, 4006800, 71550, "09:31:05", "KRX"});
    return true;
}
