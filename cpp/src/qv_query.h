#ifndef QV_QUERY_H
#define QV_QUERY_H

#include <string>
#include <vector>

#include "logger.h"
#include "qv_auth.h"
#include "types.h"

struct S8180AttemptDiagnostic {
    std::string binding_mode;
    std::string hash_source;
    std::string password_mode;
    bool hash_generation_ok = false;
    bool query_submitted = false;
    bool query_succeeded = false;
    int tr_index = 0;
    bool is_page_up = false;
    int parsed_record_count = 0;
    std::string page_cts;
    std::string next_cts;
    std::string server_message_code;
    std::string server_message;
    std::string classification;
    std::string candidate_cause;
    std::string failure_reason;
};

struct S8180Diagnostic {
    std::string trade_date;
    QVAccount selected_account;
    std::string binding_mode;
    std::string binding_mode_requested;
    std::string password_mode;
    bool hash_generation_ok = false;
    bool query_submitted = false;
    bool query_succeeded = false;
    std::string hash_source;
    std::string server_message_code;
    std::string server_message;
    std::string classification;
    std::string candidate_cause;
    std::string failure_reason;
    std::vector<S8180AttemptDiagnostic> attempts;
};

class QVQuery {
public:
    QVQuery(QVAuth& auth, Logger& logger);

    bool fetch_executions(const std::string& trade_date,
                          std::vector<ExecutionRecord>& out,
                          std::vector<std::string>& warnings);
    bool has_last_s8180_diagnostic() const;
    const S8180Diagnostic& last_s8180_diagnostic() const;

private:
    QVAuth& auth_;
    Logger& logger_;
    [[maybe_unused]] int next_exec_tr_index_ = 818000;
    [[maybe_unused]] int next_split_tr_index_ = 900000;
    S8180Diagnostic last_s8180_diagnostic_;
    bool has_last_s8180_diagnostic_ = false;

    bool fetch_s8180_page(const std::string& trade_date,
                          const std::string& cts,
                          bool is_page_up,
                          std::vector<ExecutionRecord>& page_out,
                          std::string& next_cts,
                          bool& has_more,
                          bool& fatal_error,
                          std::string& page_error);

    bool fetch_s8118_details(const std::string& trade_date,
                             const std::string& order_no,
                             std::vector<SplitDetail>& details);

    bool fill_mock_s8180(const std::string& trade_date,
                         const std::string& cts,
                         std::vector<ExecutionRecord>& page_out,
                         std::string& next_cts,
                         bool& has_more);

    bool fill_mock_s8118(const std::string& order_no,
                         std::vector<SplitDetail>& details);
};

#endif
