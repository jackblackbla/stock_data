#ifndef QV_AUTH_H
#define QV_AUTH_H

#include <string>

#include "logger.h"

class QVAuth {
public:
    explicit QVAuth(Logger& logger);
    ~QVAuth();

    bool load_dll();
    bool login();
    std::string masked_account() const;
    bool is_mock_mode() const;

private:
    Logger& logger_;
    std::string account_no_;
    bool mock_mode_ = false;

#ifdef _WIN32
    void* dll_handle_ = nullptr;
#endif
};

#endif
