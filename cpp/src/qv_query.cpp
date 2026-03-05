#include "qv_query.h"

#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <sstream>

namespace {
std::string pad_order_no(long long value) {
    std::ostringstream oss;
    oss << std::setw(10) << std::setfill('0') << value;
    return oss.str();
}

bool is_retryable_failure(int attempt, int max_attempts) {
    return attempt + 1 < max_attempts;
}
}  // namespace

QVQuery::QVQuery(QVAuth& auth, Logger& logger) : auth_(auth), logger_(logger) {}

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

        for (int attempt = 0; attempt < kMaxAttempts; ++attempt) {
            page_records.clear();
            next_cts.clear();
            next_has_more = false;

            if (fetch_s8180_page(trade_date, cts, page_up, page_records, next_cts, next_has_more)) {
                page_success = true;
                break;
            }

            logger_.warn("s8180 page fetch failed. attempt=" + std::to_string(attempt + 1));
            if (!is_retryable_failure(attempt, kMaxAttempts)) {
                return false;
            }
        }

        if (!page_success) {
            return false;
        }

        for (auto& exec : page_records) {
            if (exec.exec_qty <= 0) {
                continue;
            }

            if (exec.sor_split == "Y") {
                std::vector<SplitDetail> details;
                if (fetch_s8118_details(trade_date, exec.order_no, details) && !details.empty()) {
                    exec.split_details = details;
                } else {
                    warnings.push_back("s8118 fallback applied for order_no=" + exec.order_no);
                    if (exec.split_details.empty()) {
                        SplitDetail fallback;
                        fallback.exec_qty = exec.exec_qty;
                        fallback.exec_price = exec.exec_avg_price;
                        fallback.exec_amount = exec.exec_qty * exec.exec_avg_price;
                        fallback.exec_time = exec.exec_time;
                        fallback.market = exec.market_code;
                        exec.split_details.push_back(fallback);
                    }
                }
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
                               bool /*is_page_up*/,
                               std::vector<ExecutionRecord>& page_out,
                               std::string& next_cts,
                               bool& has_more) {
    if (auth_.is_mock_mode()) {
        return fill_mock_s8180(trade_date, cts, page_out, next_cts, has_more);
    }

    // NOTE: Hook NH QV API s8180 binding here.
    // Required behavior:
    // - Input includes CTS and ISPAGEUP
    // - Output includes next CTS and continuation flag
    // - Normalize order_no to 10-digit string
    logger_.error("s8180 binding is not integrated. Implement wmca.dll TR call in qv_query.cpp.");
    return false;
}

bool QVQuery::fetch_s8118_details(const std::string& /*trade_date*/,
                                  const std::string& order_no,
                                  std::vector<SplitDetail>& details) {
    if (auth_.is_mock_mode()) {
        return fill_mock_s8118(order_no, details);
    }

    // NOTE: Hook NH QV API s8118 binding here.
    logger_.warn("s8118 binding is not integrated. fallback to s8180 aggregate.");
    return false;
}

bool QVQuery::fill_mock_s8180(const std::string& trade_date,
                              const std::string& cts,
                              std::vector<ExecutionRecord>& page_out,
                              std::string& next_cts,
                              bool& has_more) {
    page_out.clear();

    if (cts.empty()) {
        ExecutionRecord e1;
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
