#ifndef JSON_EXPORT_H
#define JSON_EXPORT_H

#include <string>
#include <vector>

#include "logger.h"
#include "qv_auth.h"
#include "types.h"

class JsonExport {
public:
    static bool write_accounts_atomic(const std::string& output_path,
                                      const std::vector<QVAccount>& accounts,
                                      Logger& logger);

    static bool write_atomic(const std::string& output_path,
                             const std::string& trade_date,
                             const std::string& account_masked,
                             const std::vector<ExecutionRecord>& executions,
                             const std::vector<std::string>& errors,
                             Logger& logger);
};

#endif
