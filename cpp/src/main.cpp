#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "json_export.h"
#include "logger.h"
#include "qv_auth.h"
#include "qv_query.h"
#include "types.h"

#ifdef _WIN32
#include <windows.h>
#endif

namespace {
constexpr int EXIT_DLL_LOAD_FAILED = 10;
constexpr int EXIT_LOGIN_FAILED = 20;
constexpr int EXIT_TR_FAILED = 30;
constexpr int EXIT_JSON_WRITE_FAILED = 40;

struct BatchAccountSelection {
    int account_index = 0;
    std::string account_no;
    std::string account_password;
};

struct Args {
    std::string date;
    std::string output;
    std::string log;
    bool list_accounts = false;
    bool session_mode = false;
};

#ifdef _WIN32
Logger* g_crash_logger = nullptr;

std::string hex32(unsigned long value) {
    std::ostringstream oss;
    oss << "0x" << std::uppercase << std::hex << value;
    return oss.str();
}

std::string hex_ptr(void* value) {
    std::ostringstream oss;
    oss << "0x" << std::uppercase << std::hex << reinterpret_cast<std::uintptr_t>(value);
    return oss.str();
}

LONG WINAPI log_unhandled_exception(EXCEPTION_POINTERS* exception_info) {
    if (g_crash_logger != nullptr && exception_info != nullptr && exception_info->ExceptionRecord != nullptr) {
        const auto* record = exception_info->ExceptionRecord;
        g_crash_logger->error(
            "Unhandled SEH exception code=" + hex32(record->ExceptionCode) +
            " address=" + hex_ptr(record->ExceptionAddress));
    }
    return EXCEPTION_EXECUTE_HANDLER;
}
#endif

bool is_valid_date(const std::string& value) {
    if (value.size() != 8) {
        return false;
    }
    for (char c : value) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}

std::string env_or_empty(const char* key) {
    const char* value = std::getenv(key);
    if (value == nullptr) {
        return "";
    }
    return std::string(value);
}

std::string trim(const std::string& value) {
    std::size_t start = 0;
    while (start < value.size() && std::isspace(static_cast<unsigned char>(value[start])) != 0) {
        ++start;
    }
    std::size_t end = value.size();
    while (end > start && std::isspace(static_cast<unsigned char>(value[end - 1])) != 0) {
        --end;
    }
    return value.substr(start, end - start);
}

bool contains_protocol_delimiter(const std::string& value) {
    return value.find('\t') != std::string::npos ||
           value.find('\r') != std::string::npos ||
           value.find('\n') != std::string::npos;
}

bool is_digit_4_password(const std::string& value) {
    if (value.size() != 4) {
        return false;
    }
    return std::all_of(value.begin(), value.end(), [](unsigned char c) {
        return std::isdigit(c) != 0;
    });
}

std::vector<std::string> split(const std::string& input, char delimiter) {
    std::vector<std::string> out;
    std::size_t start = 0;
    while (start <= input.size()) {
        const std::size_t pos = input.find(delimiter, start);
        if (pos == std::string::npos) {
            out.push_back(input.substr(start));
            break;
        }
        out.push_back(input.substr(start, pos - start));
        start = pos + 1;
    }
    return out;
}

bool parse_batch_accounts(const std::string& raw,
                          std::vector<BatchAccountSelection>& out,
                          std::string& error_message) {
    out.clear();
    if (raw.empty()) {
        return true;
    }

    const std::vector<std::string> items = split(raw, ';');
    for (const auto& item_raw : items) {
        const std::string item = trim(item_raw);
        if (item.empty()) {
            continue;
        }

        const std::vector<std::string> fields = split(item, '|');
        if (fields.size() != 3) {
            error_message = "invalid QV_BATCH_ACCOUNTS item: " + item;
            return false;
        }

        BatchAccountSelection selection;
        try {
            selection.account_index = std::stoi(trim(fields[0]));
        } catch (...) {
            error_message = "invalid account index in QV_BATCH_ACCOUNTS: " + item;
            return false;
        }
        selection.account_no = trim(fields[1]);
        selection.account_password = trim(fields[2]);
        if (selection.account_index <= 0 || selection.account_no.empty() || selection.account_password.empty()) {
            error_message = "incomplete QV_BATCH_ACCOUNTS item: " + item;
            return false;
        }
        out.push_back(selection);
    }

    return true;
}

std::string escape_json(const std::string& src) {
    std::string out;
    out.reserve(src.size() + 8);
    for (char c : src) {
        switch (c) {
            case '\\':
                out += "\\\\";
                break;
            case '"':
                out += "\\\"";
                break;
            case '\n':
                out += "\\n";
                break;
            case '\r':
                out += "\\r";
                break;
            case '\t':
                out += "\\t";
                break;
            default:
                out.push_back(c);
                break;
        }
    }
    return out;
}

void write_session_error(const std::string& message) {
    std::cout << "{\"ok\":false,\"error\":\"" << escape_json(message) << "\"}" << std::endl;
}

void write_session_accounts(const std::vector<QVAccount>& accounts) {
    std::ostringstream out;
    out << "{\"ok\":true,\"accounts\":[";
    for (std::size_t i = 0; i < accounts.size(); ++i) {
        const auto& account = accounts[i];
        out << "{\"account_index\":" << account.account_index
            << ",\"account_no\":\"" << escape_json(account.account_no) << "\"}";
        if (i + 1 < accounts.size()) {
            out << ",";
        }
    }
    out << "]}";
    std::cout << out.str() << std::endl;
}

void write_session_output_ok(const std::string& output_path) {
    std::cout << "{\"ok\":true,\"output\":\"" << escape_json(output_path) << "\"}" << std::endl;
}

void write_session_message_ok(const std::string& message) {
    std::cout << "{\"ok\":true,\"message\":\"" << escape_json(message) << "\"}" << std::endl;
}

bool read_protocol_line(std::string& out) {
    if (!std::getline(std::cin, out)) {
        return false;
    }
    if (!out.empty() && out.back() == '\r') {
        out.pop_back();
    }
    return true;
}

bool parse_session_selection_line(const std::string& line,
                                  BatchAccountSelection& selection,
                                  std::string& error_message) {
    const std::vector<std::string> fields = split(line, '\t');
    if (fields.size() != 3) {
        error_message = "invalid selection line";
        return false;
    }
    try {
        selection.account_index = std::stoi(trim(fields[0]));
    } catch (...) {
        error_message = "invalid account index";
        return false;
    }
    selection.account_no = trim(fields[1]);
    selection.account_password = trim(fields[2]);
    if (selection.account_index <= 0 || selection.account_no.empty() || selection.account_password.empty()) {
        error_message = "incomplete account selection";
        return false;
    }
    if (contains_protocol_delimiter(selection.account_no) || contains_protocol_delimiter(selection.account_password)) {
        error_message = "invalid control character in account selection";
        return false;
    }
    if (!is_digit_4_password(selection.account_password)) {
        error_message = "account password must be exactly 4 digits";
        return false;
    }
    return true;
}

bool run_batch_query(QVAuth& auth,
                     Logger& logger,
                     const std::string& trade_date,
                     const std::string& output_path,
                     const std::vector<BatchAccountSelection>& batch_accounts,
                     std::string& error_message) {
    if (batch_accounts.empty()) {
        error_message = "no selected accounts";
        return false;
    }

    QVQuery query(auth, logger);
    std::vector<ExecutionRecord> executions;
    std::vector<std::string> messages;
    std::vector<QVAccount> queried_accounts;
    int success_count = 0;

    for (const auto& selection : batch_accounts) {
        std::string activate_error;
        if (!auth.set_active_account(selection.account_index, selection.account_password, activate_error)) {
            const std::string error = selection.account_no + ": " + activate_error;
            logger.error("Batch account selection failed: " + error);
            messages.push_back(error);
            continue;
        }

        queried_accounts.push_back(QVAccount{auth.account_index(), auth.account_no()});
        logger.info(
            "Batch account query start account_index=" + std::to_string(auth.account_index()) +
            " account_no=" + auth.account_no());

        std::vector<ExecutionRecord> per_account_executions;
        std::vector<std::string> per_account_warnings;
        if (!query.fetch_executions(trade_date, per_account_executions, per_account_warnings)) {
            std::string account_error = "TR 조회 실패";
            if (!per_account_warnings.empty()) {
                account_error = per_account_warnings.back();
            }
            const std::string error = auth.account_no() + ": " + account_error;
            logger.error("Batch account query failed: " + error);
            messages.push_back(error);
            continue;
        }

        executions.insert(executions.end(), per_account_executions.begin(), per_account_executions.end());
        for (const auto& warning : per_account_warnings) {
            messages.push_back(auth.account_no() + ": " + warning);
        }
        ++success_count;
    }

    if (success_count == 0) {
        error_message = "All batch account queries failed.";
        logger.error(error_message);
        return false;
    }

    const std::string root_account = queried_accounts.size() > 1
        ? "MULTI"
        : (queried_accounts.empty() ? auth.account_no() : queried_accounts.front().account_no);
    if (!JsonExport::write_atomic(
            output_path,
            trade_date,
            root_account,
            queried_accounts,
            executions,
            messages,
            logger)) {
        error_message = "failed to write output JSON";
        return false;
    }

    logger.info(
        "fetch.exe completed successfully. records=" + std::to_string(executions.size()) +
        " queried_accounts=" + std::to_string(queried_accounts.size()));
    return true;
}

int run_session_loop(QVAuth& auth, Logger& logger) {
    bool logged_in = false;

    while (true) {
        std::string command;
        if (!read_protocol_line(command)) {
            return 0;
        }
        command = trim(command);
        if (command.empty()) {
            continue;
        }

        if (command == "LOGIN") {
            std::string user_id;
            std::string password;
            std::string cert_password;
            if (!read_protocol_line(user_id) || !read_protocol_line(password) || !read_protocol_line(cert_password)) {
                write_session_error("invalid login command payload");
                return 1;
            }
            if (logged_in) {
                write_session_error("session already logged in");
                continue;
            }
            if (!auth.login_with_credentials(trim(user_id), trim(password), trim(cert_password), "", false)) {
                write_session_error("login failed");
                continue;
            }
            logged_in = true;
            write_session_accounts(auth.accounts());
            continue;
        }

        if (command == "QUERY") {
            std::string trade_date;
            std::string output_path;
            std::string count_raw;
            if (!read_protocol_line(trade_date) || !read_protocol_line(output_path) || !read_protocol_line(count_raw)) {
                write_session_error("invalid query command payload");
                return 1;
            }
            if (!logged_in) {
                write_session_error("session is not logged in");
                continue;
            }
            trade_date = trim(trade_date);
            output_path = trim(output_path);
            if (!is_valid_date(trade_date) || output_path.empty()) {
                write_session_error("invalid query arguments");
                continue;
            }
            int count = 0;
            try {
                count = std::stoi(trim(count_raw));
            } catch (...) {
                write_session_error("invalid account selection count");
                continue;
            }
            if (count <= 0) {
                write_session_error("no selected accounts");
                continue;
            }

            std::vector<BatchAccountSelection> selections;
            selections.reserve(static_cast<std::size_t>(count));
            bool parse_failed = false;
            int consumed = 0;
            for (int i = 0; i < count; ++i) {
                std::string line;
                if (!read_protocol_line(line)) {
                    write_session_error("incomplete query selection payload");
                    return 1;
                }
                ++consumed;
                BatchAccountSelection selection;
                std::string parse_error;
                if (!parse_session_selection_line(line, selection, parse_error)) {
                    write_session_error(parse_error);
                    parse_failed = true;
                    break;
                }
                logger.info(
                    "Session QUERY selection account_index=" + std::to_string(selection.account_index) +
                    " account_no=" + selection.account_no +
                    " password_length=" + std::to_string(selection.account_password.size()) +
                    " is_digit_4=" + std::string(is_digit_4_password(selection.account_password) ? "Y" : "N"));
                selections.push_back(selection);
            }
            if (parse_failed) {
                for (int i = consumed; i < count; ++i) {
                    std::string discard;
                    if (!read_protocol_line(discard)) {
                        return 1;
                    }
                }
                continue;
            }

            std::string run_error;
            if (!run_batch_query(auth, logger, trade_date, output_path, selections, run_error)) {
                write_session_error(run_error);
                continue;
            }
            write_session_output_ok(output_path);
            continue;
        }

        if (command == "SHUTDOWN") {
            write_session_message_ok("shutdown");
            return 0;
        }

        write_session_error("unknown command: " + command);
    }
}

void print_usage() {
    std::cerr << "Usage: fetch.exe --date YYYYMMDD --output <json_path> [--log <log_path>]\n"
              << "   or: fetch.exe --list-accounts --output <json_path> [--log <log_path>]\n"
              << "   or: fetch.exe --session [--log <log_path>]" << std::endl;
}

bool parse_args(int argc, char* argv[], Args& args) {
    for (int i = 1; i < argc; ++i) {
        const std::string token(argv[i]);
        if (token == "--date" && i + 1 < argc) {
            args.date = argv[++i];
            continue;
        }
        if (token == "--output" && i + 1 < argc) {
            args.output = argv[++i];
            continue;
        }
        if (token == "--log" && i + 1 < argc) {
            args.log = argv[++i];
            continue;
        }
        if (token == "--list-accounts") {
            args.list_accounts = true;
            continue;
        }
        if (token == "--session") {
            args.session_mode = true;
            continue;
        }
        return false;
    }

    if (!args.session_mode && args.output.empty()) {
        return false;
    }
    if (!args.session_mode && !args.list_accounts && !is_valid_date(args.date)) {
        return false;
    }
    if (args.log.empty()) {
        if (args.session_mode) {
            args.log = "logs/fetch_session.log";
        } else {
            args.log = args.list_accounts ? "logs/fetch_accounts.log" : "logs/fetch_" + args.date + ".log";
        }
    }
    return true;
}
}  // namespace

int main(int argc, char* argv[]) {
    Args args;
    if (!parse_args(argc, argv, args)) {
        print_usage();
        return 1;
    }

    try {
        const std::filesystem::path log_path(args.log);
        if (log_path.has_parent_path()) {
            std::filesystem::create_directories(log_path.parent_path());
        }

        if (!args.session_mode) {
            const std::filesystem::path output_path(args.output);
            if (output_path.has_parent_path()) {
                std::filesystem::create_directories(output_path.parent_path());
            }
        }

        Logger logger(args.log, !args.session_mode);
        if (args.session_mode) {
            logger.info("fetch.exe started in session mode");
        } else if (args.list_accounts) {
            logger.info("fetch.exe started for account listing");
        } else {
            logger.info("fetch.exe started for trade date: " + args.date);
        }
        logger.info(std::string("fetch.exe build: ") + __DATE__ + " " + __TIME__);
#ifdef _WIN32
        g_crash_logger = &logger;
        SetUnhandledExceptionFilter(log_unhandled_exception);
#endif

        QVAuth auth(logger);
        if (!auth.load_dll()) {
            return EXIT_DLL_LOAD_FAILED;
        }

        if (args.session_mode) {
            return run_session_loop(auth, logger);
        }

        std::vector<BatchAccountSelection> batch_accounts;
        const std::string batch_accounts_raw = env_or_empty("QV_BATCH_ACCOUNTS");
        std::string batch_parse_error;
        if (!parse_batch_accounts(batch_accounts_raw, batch_accounts, batch_parse_error)) {
            logger.error(batch_parse_error);
            return EXIT_TR_FAILED;
        }

        const bool batch_mode = !batch_accounts.empty();
        if (batch_mode) {
            logger.info("Batch account query enabled. selected_accounts=" + std::to_string(batch_accounts.size()));
        }

        if (!auth.login(!args.list_accounts && !batch_mode)) {
            return EXIT_LOGIN_FAILED;
        }

        if (args.list_accounts) {
            if (!JsonExport::write_accounts_atomic(args.output, auth.accounts(), logger)) {
                return EXIT_JSON_WRITE_FAILED;
            }
            logger.info("fetch.exe completed successfully. accounts=" + std::to_string(auth.accounts().size()));
            return 0;
        }

        if (batch_mode) {
            std::string run_error;
            if (!run_batch_query(auth, logger, args.date, args.output, batch_accounts, run_error)) {
                logger.error(run_error);
                return EXIT_TR_FAILED;
            }
            return 0;
        }

        QVQuery query(auth, logger);
        std::vector<ExecutionRecord> executions;
        std::vector<std::string> warnings;
        if (!query.fetch_executions(args.date, executions, warnings)) {
            logger.error("s8180 query failed after retry.");
            return EXIT_TR_FAILED;
        }

        if (!JsonExport::write_atomic(
                args.output,
                args.date,
                auth.account_no(),
                std::vector<QVAccount>{QVAccount{auth.account_index(), auth.account_no()}},
                executions,
                warnings,
                logger)) {
            return EXIT_JSON_WRITE_FAILED;
        }

        logger.info("fetch.exe completed successfully. records=" + std::to_string(executions.size()));
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Unhandled error: " << ex.what() << std::endl;
        return 1;
    }
}
