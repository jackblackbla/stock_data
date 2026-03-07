#ifndef QV_QUERY_H
#define QV_QUERY_H

#include <string>
#include <vector>

#include "logger.h"
#include "qv_auth.h"
#include "types.h"

class QVQuery {
public:
    QVQuery(QVAuth& auth, Logger& logger);

    bool fetch_executions(const std::string& trade_date,
                          std::vector<ExecutionRecord>& out,
                          std::vector<std::string>& warnings);

private:
    QVAuth& auth_;
    Logger& logger_;
    [[maybe_unused]] int next_exec_tr_index_ = 818000;
    [[maybe_unused]] int next_split_tr_index_ = 900000;

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
