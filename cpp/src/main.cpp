#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "json_export.h"
#include "logger.h"
#include "qv_auth.h"
#include "qv_query.h"
#include "types.h"

namespace {
constexpr int EXIT_DLL_LOAD_FAILED = 10;
constexpr int EXIT_LOGIN_FAILED = 20;
constexpr int EXIT_TR_FAILED = 30;
constexpr int EXIT_JSON_WRITE_FAILED = 40;

struct Args {
    std::string date;
    std::string output;
    std::string log;
};

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

void print_usage() {
    std::cerr << "Usage: fetch.exe --date YYYYMMDD --output <json_path> [--log <log_path>]" << std::endl;
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
        return false;
    }

    if (args.date.empty() || args.output.empty()) {
        return false;
    }
    if (!is_valid_date(args.date)) {
        return false;
    }
    if (args.log.empty()) {
        args.log = "logs/fetch_" + args.date + ".log";
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

        const std::filesystem::path output_path(args.output);
        if (output_path.has_parent_path()) {
            std::filesystem::create_directories(output_path.parent_path());
        }

        Logger logger(args.log);
        logger.info("fetch.exe started for trade date: " + args.date);

        QVAuth auth(logger);
        if (!auth.load_dll()) {
            return EXIT_DLL_LOAD_FAILED;
        }

        if (!auth.login()) {
            return EXIT_LOGIN_FAILED;
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
                auth.masked_account(),
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
