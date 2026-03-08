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

void write_double(std::ofstream& out, const std::string& key, double value, bool comma = true) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(6) << value;
    out << "\"" << key << "\":" << oss.str();
    if (comma) {
        out << ",";
    }
}

void write_bool(std::ofstream& out, const std::string& key, bool value, bool comma = true) {
    out << "\"" << key << "\":" << (value ? "true" : "false");
    if (comma) {
        out << ",";
    }
}

void write_string_array(std::ofstream& out,
                        const std::string& key,
                        const std::vector<std::string>& values,
                        bool comma = true) {
    out << "\"" << key << "\":[";
    for (std::size_t i = 0; i < values.size(); ++i) {
        out << "\"" << escape_json(values[i]) << "\"";
        if (i + 1 < values.size()) {
            out << ",";
        }
    }
    out << "]";
    if (comma) {
        out << ",";
    }
}

void write_account(std::ofstream& out, const QVAccount& account, bool comma = true) {
    out << "{";
    write_number(out, "account_index", account.account_index);
    write_string(out, "account_no", account.account_no);
    write_string(out, "account_name", account.account_name);
    write_string(out, "act_pdt_cd", account.act_pdt_cd);
    write_string(out, "amn_tab_cd", account.amn_tab_cd);
    write_string(out, "expr_date", account.expr_date);
    write_string(out, "granted", account.granted);
    write_bool(out, "is_granted_batch", account.is_granted_batch);
    write_string_array(out, "diagnostic_labels", account.diagnostic_labels, false);
    out << "}";
    if (comma) {
        out << ",";
    }
}

void write_s8180_attempt(std::ofstream& out, const S8180AttemptDiagnostic& attempt, bool comma = true) {
    out << "{";
    write_string(out, "binding_mode", attempt.binding_mode);
    write_string(out, "hash_source", attempt.hash_source);
    write_string(out, "password_mode", attempt.password_mode);
    write_bool(out, "hash_generation_ok", attempt.hash_generation_ok);
    write_bool(out, "trade_password_present", attempt.trade_password_present);
    write_number(out, "trade_password_length", attempt.trade_password_length);
    write_bool(out, "trade_hash_generation_ok", attempt.trade_hash_generation_ok);
    write_string(out, "trade_hash_source", attempt.trade_hash_source);
    write_bool(out, "query_submitted", attempt.query_submitted);
    write_bool(out, "query_succeeded", attempt.query_succeeded);
    write_number(out, "tr_index", attempt.tr_index);
    write_bool(out, "is_page_up", attempt.is_page_up);
    write_number(out, "parsed_record_count", attempt.parsed_record_count);
    write_string(out, "page_cts", attempt.page_cts);
    write_string(out, "next_cts", attempt.next_cts);
    write_string(out, "server_message_code", attempt.server_message_code);
    write_string(out, "server_message", attempt.server_message);
    write_string(out, "classification", attempt.classification);
    write_string(out, "candidate_cause", attempt.candidate_cause);
    write_string(out, "failure_reason", attempt.failure_reason, false);
    out << "}";
    if (comma) {
        out << ",";
    }
}

void write_s8180_diagnostic_body(std::ofstream& out, const S8180Diagnostic& diagnostic, bool comma = true) {
    out << "{";
    write_string(out, "binding_mode", diagnostic.binding_mode);
    write_string(out, "binding_mode_requested", diagnostic.binding_mode_requested);
    write_string(out, "password_mode", diagnostic.password_mode);
    write_bool(out, "hash_generation_ok", diagnostic.hash_generation_ok);
    write_bool(out, "trade_password_present", diagnostic.trade_password_present);
    write_number(out, "trade_password_length", diagnostic.trade_password_length);
    write_bool(out, "trade_hash_generation_ok", diagnostic.trade_hash_generation_ok);
    write_bool(out, "query_submitted", diagnostic.query_submitted);
    write_bool(out, "query_succeeded", diagnostic.query_succeeded);
    write_string(out, "hash_source", diagnostic.hash_source);
    write_string(out, "trade_hash_source", diagnostic.trade_hash_source);
    write_string(out, "server_message_code", diagnostic.server_message_code);
    write_string(out, "server_message", diagnostic.server_message);
    write_string(out, "classification", diagnostic.classification);
    write_string(out, "candidate_cause", diagnostic.candidate_cause);
    write_string(out, "failure_reason", diagnostic.failure_reason);
    out << "\"attempts\":[";
    for (std::size_t i = 0; i < diagnostic.attempts.size(); ++i) {
        write_s8180_attempt(out, diagnostic.attempts[i], i + 1 < diagnostic.attempts.size());
    }
    out << "]";
    out << "}";
    if (comma) {
        out << ",";
    }
}

void write_s8180_diagnostic_entry(std::ofstream& out, const S8180Diagnostic& diagnostic, bool comma = true) {
    out << "{";
    out << "\"selected_account\":";
    write_account(out, diagnostic.selected_account, false);
    out << ",\"s8180_diagnostic\":";
    write_s8180_diagnostic_body(out, diagnostic, false);
    out << "}";
    if (comma) {
        out << ",";
    }
}

void write_balance_summary(std::ofstream& out, const BalanceSummary& summary, bool comma = true) {
    out << "{";
    write_string(out, "account_no", summary.account_no);
    write_number(out, "deposit_amount", summary.deposit_amount);
    write_number(out, "withdrawable_amount", summary.withdrawable_amount);
    write_number(out, "orderable_amount", summary.orderable_amount);
    write_number(out, "cash_margin", summary.cash_margin);
    write_number(out, "substitute_margin", summary.substitute_margin);
    write_number(out, "d1_deposit", summary.d1_deposit);
    write_number(out, "d2_deposit", summary.d2_deposit);
    write_number(out, "purchase_amount_total", summary.purchase_amount_total);
    write_number(out, "valuation_amount_total", summary.valuation_amount_total);
    write_number(out, "net_asset_amount", summary.net_asset_amount);
    write_number(out, "total_profit_loss", summary.total_profit_loss);
    write_double(out, "profit_rate", summary.profit_rate);
    write_number(out, "net_total_asset_amount", summary.net_total_asset_amount);
    write_string(out, "activity_type", summary.activity_type, false);
    out << "}";
    if (comma) {
        out << ",";
    }
}

void write_balance_position(std::ofstream& out, const BalancePosition& position, bool comma = true) {
    out << "{";
    write_string(out, "account_no", position.account_no);
    write_string(out, "stock_code", position.stock_code);
    write_string(out, "stock_name", position.stock_name);
    write_string(out, "balance_type", position.balance_type);
    write_string(out, "loan_date", position.loan_date);
    write_number(out, "quantity", position.quantity);
    write_number(out, "unsettled_quantity", position.unsettled_quantity);
    write_number(out, "avg_buy_price", position.avg_buy_price);
    write_number(out, "current_price", position.current_price);
    write_number(out, "profit_loss", position.profit_loss);
    write_double(out, "profit_rate", position.profit_rate);
    write_string(out, "credit_type", position.credit_type);
    write_number(out, "remaining_quantity", position.remaining_quantity);
    write_string(out, "expiry_date", position.expiry_date);
    write_number(out, "valuation_amount", position.valuation_amount);
    write_string(out, "issue_margin_rate", position.issue_margin_rate);
    write_number(out, "avg_sell_price", position.avg_sell_price);
    write_number(out, "sell_profit_loss", position.sell_profit_loss, false);
    out << "}";
    if (comma) {
        out << ",";
    }
}

void write_balance_account_result(std::ofstream& out, const BalanceAccountResult& result, bool comma = true) {
    out << "{";
    out << "\"selected_account\":";
    write_account(out, result.selected_account, false);
    out << ",\"summary\":";
    write_balance_summary(out, result.summary, false);
    out << ",\"positions\":[";
    for (std::size_t i = 0; i < result.positions.size(); ++i) {
        write_balance_position(out, result.positions[i], i + 1 < result.positions.size());
    }
    out << "],";
    write_string_array(out, "warnings", result.warnings, false);
    out << "}";
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
            write_account(out, accounts[i], i + 1 < accounts.size());
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
                              const std::string& account_no,
                              const std::vector<QVAccount>& accounts,
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
        write_string(out, "account_no", account_no);
        write_string(out, "status", errors.empty() ? "ok" : "partial");

        out << "\"errors\":[";
        for (std::size_t i = 0; i < errors.size(); ++i) {
            out << "\"" << escape_json(errors[i]) << "\"";
            if (i + 1 < errors.size()) {
                out << ",";
            }
        }
        out << "],";

        out << "\"accounts\":[";
        for (std::size_t i = 0; i < accounts.size(); ++i) {
            write_account(out, accounts[i], i + 1 < accounts.size());
        }
        out << "],";

        out << "\"executions\":[";
        for (std::size_t i = 0; i < executions.size(); ++i) {
            const auto& e = executions[i];
            out << "{";
            write_string(out, "account_no", e.account_no);
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

bool JsonExport::write_s8180_diagnostics_atomic(const std::string& output_path,
                                                const std::string& trade_date,
                                                const std::vector<S8180Diagnostic>& diagnostics,
                                                Logger& logger) {
    try {
        const std::filesystem::path out_path(output_path);
        const std::filesystem::path tmp_path = out_path.string() + ".tmp";

        if (out_path.has_parent_path()) {
            std::filesystem::create_directories(out_path.parent_path());
        }

        std::ofstream out(tmp_path, std::ios::trunc);
        if (!out.is_open()) {
            logger.error("Cannot open tmp file for diagnostic JSON: " + tmp_path.string());
            return false;
        }

        out << "{";
        write_string(out, "schema_version", "1.0");
        write_string(out, "generated_at", now_iso_local());
        write_string(out, "trade_date", trade_date);
        out << "\"account_diagnostics\":[";
        for (std::size_t i = 0; i < diagnostics.size(); ++i) {
            write_s8180_diagnostic_entry(out, diagnostics[i], i + 1 < diagnostics.size());
        }
        out << "]";
        if (diagnostics.size() == 1) {
            out << ",";
            out << "\"selected_account\":";
            write_account(out, diagnostics.front().selected_account, false);
            out << ",\"s8180_diagnostic\":";
            write_s8180_diagnostic_body(out, diagnostics.front(), false);
        }
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
                logger.error("Atomic rename failed for diagnostic JSON.");
                return false;
            }
        }

        logger.info("Diagnostic JSON exported: " + out_path.string());
        return true;
    } catch (const std::exception& ex) {
        logger.error(std::string("Diagnostic JSON export exception: ") + ex.what());
        return false;
    }
}

bool JsonExport::write_balance_atomic(const std::string& output_path,
                                      const std::vector<BalanceAccountResult>& results,
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
            logger.error("Cannot open tmp file for balance JSON: " + tmp_path.string());
            return false;
        }

        out << "{";
        write_string(out, "schema_version", "1.0");
        write_string(out, "generated_at", now_iso_local());
        write_string(out, "status", results.empty() ? "error" : (errors.empty() ? "ok" : "partial"));
        out << "\"errors\":[";
        for (std::size_t i = 0; i < errors.size(); ++i) {
            out << "\"" << escape_json(errors[i]) << "\"";
            if (i + 1 < errors.size()) {
                out << ",";
            }
        }
        out << "],";
        out << "\"balance_accounts\":[";
        for (std::size_t i = 0; i < results.size(); ++i) {
            write_balance_account_result(out, results[i], i + 1 < results.size());
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
                logger.error("Atomic rename failed for balance JSON.");
                return false;
            }
        }

        logger.info("Balance JSON exported: " + out_path.string());
        return true;
    } catch (const std::exception& ex) {
        logger.error(std::string("Balance JSON export exception: ") + ex.what());
        return false;
    }
}
