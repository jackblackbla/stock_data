#ifndef JSON_EXPORT_H
#define JSON_EXPORT_H

#include <string>
#include <vector>

#include "logger.h"
#include "qv_auth.h"
#include "qv_query.h"
#include "types.h"

class JsonExport {
public:
    static bool write_accounts_atomic(const std::string& output_path,
                                      const std::vector<QVAccount>& accounts,
                                      Logger& logger);

    static bool write_atomic(const std::string& output_path,
                             const std::string& trade_date,
                             const std::string& account_no,
                             const std::vector<QVAccount>& accounts,
                             const std::vector<ExecutionRecord>& executions,
                             const std::vector<std::string>& errors,
                             Logger& logger);

    static bool write_s8180_diagnostics_atomic(const std::string& output_path,
                                               const std::string& trade_date,
                                               const std::vector<S8180Diagnostic>& diagnostics,
                                               Logger& logger);

    static bool write_balance_atomic(const std::string& output_path,
                                     const std::vector<BalanceAccountResult>& results,
                                     const std::vector<std::string>& errors,
                                     Logger& logger);
};

#endif
