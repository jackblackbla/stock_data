#include "json_export.h"

#include <chrono>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>

namespace {
std::string now_iso_local() {
    const auto now = std::chrono::system_clock::now();
    const auto tt = std::chrono::system_clock::to_time_t(now);
    std::tm tm_now{};
#ifdef _WIN32
    localtime_s(&tm_now, &tt);
#else
    localtime_r(&tt, &tm_now);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm_now, "%Y-%m-%dT%H:%M:%S");
    return oss.str();
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

void write_string(std::ofstream& out, const std::string& key, const std::string& value, bool comma = true) {
    out << "\"" << key << "\":\"" << escape_json(value) << "\"";
    if (comma) {
        out << ",";
    }
}

void write_number(std::ofstream& out, const std::string& key, long long value, bool comma = true) {
    out << "\"" << key << "\":" << value;
    if (comma) {
        out << ",";
    }
}
}  // namespace

bool JsonExport::write_accounts_atomic(const std::string& output_path,
                                       const std::vector<QVAccount>& accounts,
                                       Logger& logger) {
    try {
        const std::filesystem::path out_path(output_path);
        const std::filesystem::path tmp_path = out_path.string() + ".tmp";

        if (out_path.has_parent_path()) {
            std::filesystem::create_directories(out_path.parent_path());
        }

        std::ofstream out(tmp_path, std::ios::trunc);
        if (!out.is_open()) {
            logger.error("Cannot open tmp file for accounts JSON: " + tmp_path.string());
            return false;
        }

        out << "{";
        write_string(out, "schema_version", "1.0");
        write_string(out, "generated_at", now_iso_local());
        out << "\"accounts\":[";
        for (std::size_t i = 0; i < accounts.size(); ++i) {
            const auto& account = accounts[i];
            out << "{";
            write_number(out, "account_index", account.account_index);
            write_string(out, "account_masked", account.account_masked, false);
            out << "}";
            if (i + 1 < accounts.size()) {
                out << ",";
            }
        }
        out << "]";
        out << "}";

        out.flush();
        out.close();

        std::error_code rename_ec;
        std::filesystem::rename(tmp_path, out_path, rename_ec);
        if (rename_ec) {
            std::error_code remove_ec;
            std::filesystem::remove(out_path, remove_ec);
            rename_ec.clear();
            std::filesystem::rename(tmp_path, out_path, rename_ec);
            if (rename_ec) {
                logger.error("Atomic rename failed for accounts JSON.");
                return false;
            }
        }

        logger.info("Accounts JSON exported: " + out_path.string());
        return true;
    } catch (const std::exception& ex) {
        logger.error(std::string("Accounts JSON export exception: ") + ex.what());
        return false;
    }
}

bool JsonExport::write_atomic(const std::string& output_path,
                              const std::string& trade_date,
                              const std::string& account_masked,
                              const std::vector<ExecutionRecord>& executions,
                              const std::vector<std::string>& errors,
                              Logger& logger) {
    try {
        const std::filesystem::path out_path(output_path);
        const std::filesystem::path tmp_path = out_path.string() + ".tmp";

        if (out_path.has_parent_path()) {
            std::filesystem::create_directories(out_path.parent_path());
        }

        std::ofstream out(tmp_path, std::ios::trunc);
        if (!out.is_open()) {
            logger.error("Cannot open tmp file for JSON: " + tmp_path.string());
            return false;
        }

        out << "{";
        write_string(out, "schema_version", "1.0");
        write_string(out, "trade_date", trade_date);
        write_string(out, "generated_at", now_iso_local());
        write_string(out, "account_masked", account_masked);
        write_string(out, "status", errors.empty() ? "ok" : "partial");

        out << "\"errors\":[";
        for (std::size_t i = 0; i < errors.size(); ++i) {
            out << "\"" << escape_json(errors[i]) << "\"";
            if (i + 1 < errors.size()) {
                out << ",";
            }
        }
        out << "],";

        out << "\"executions\":[";
        for (std::size_t i = 0; i < executions.size(); ++i) {
            const auto& e = executions[i];
            out << "{";
            write_string(out, "account_masked", e.account_masked);
            write_string(out, "order_no", e.order_no);
            write_string(out, "orig_order_no", e.orig_order_no);
            write_string(out, "order_type", e.order_type);
            write_string(out, "stock_code", e.stock_code);
            write_string(out, "stock_name", e.stock_name);
            write_number(out, "order_qty", e.order_qty);
            write_number(out, "exec_qty", e.exec_qty);
            write_number(out, "order_price", e.order_price);
            write_number(out, "exec_avg_price", e.exec_avg_price);
            write_string(out, "exec_time", e.exec_time);
            write_string(out, "market_code", e.market_code);
            write_string(out, "sor_split", e.sor_split);

            out << "\"split_details\":[";
            for (std::size_t j = 0; j < e.split_details.size(); ++j) {
                const auto& d = e.split_details[j];
                out << "{";
                write_number(out, "exec_qty", d.exec_qty);
                write_number(out, "exec_amount", d.exec_amount);
                write_number(out, "exec_price", d.exec_price);
                write_string(out, "exec_time", d.exec_time);
                write_string(out, "market", d.market, false);
                out << "}";
                if (j + 1 < e.split_details.size()) {
                    out << ",";
                }
            }
            out << "]";
            out << "}";
            if (i + 1 < executions.size()) {
                out << ",";
            }
        }
        out << "]";
        out << "}";

        out.flush();
        out.close();

        std::error_code rename_ec;
        std::filesystem::rename(tmp_path, out_path, rename_ec);
        if (rename_ec) {
            std::error_code remove_ec;
            std::filesystem::remove(out_path, remove_ec);
            rename_ec.clear();
            std::filesystem::rename(tmp_path, out_path, rename_ec);
            if (rename_ec) {
                logger.error("Atomic rename failed for output JSON.");
                return false;
            }
        }

        logger.info("JSON exported: " + out_path.string());
        return true;
    } catch (const std::exception& ex) {
        logger.error(std::string("JSON export exception: ") + ex.what());
        return false;
    }
}
