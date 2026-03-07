#ifndef QV_AUTH_H
#define QV_AUTH_H

#include <cstdint>
#include <string>
#include <vector>

#include "logger.h"

struct QVEvent {
    std::uint32_t code = 0;
    std::intptr_t raw_lparam = 0;
    int tr_index = 0;
    std::string block_name;
    std::vector<char> data;
    int data_len = 0;
};

struct QVAccount {
    int account_index = 1;
    std::string account_no;
    std::string account_masked;
};

class QVAuth {
public:
    explicit QVAuth(Logger& logger);
    ~QVAuth();

    bool load_dll();
    bool login(bool require_account_password = true);
    bool submit_query(int tr_index,
                      const std::string& tr_code,
                      const void* input,
                      int input_size) const;
    bool wait_for_event(QVEvent& event, int timeout_ms, std::string& error_message) const;

    std::string masked_account() const;
    int account_index() const;
    const std::string& account_password() const;
    const std::vector<QVAccount>& accounts() const;
    bool is_mock_mode() const;

private:
    Logger& logger_;
    std::string account_no_;
    std::string account_password_;
    int account_index_ = 1;
    std::vector<QVAccount> accounts_;
    bool mock_mode_ = false;

#ifdef _WIN32
    using WmcaLoad = int(__stdcall*)();
    using WmcaFree = int(__stdcall*)();
    using WmcaConnect = int(__stdcall*)(void*, unsigned long, char, char, const char*, const char*, const char*);
    using WmcaDisconnect = int(__stdcall*)();
    using WmcaQuery = int(__stdcall*)(void*, int, const char*, const char*, int, int);

    void* dll_handle_ = nullptr;
    void* hwnd_ = nullptr;
    WmcaLoad wmca_load_ = nullptr;
    WmcaFree wmca_free_ = nullptr;
    WmcaConnect wmca_connect_ = nullptr;
    WmcaDisconnect wmca_disconnect_ = nullptr;
    WmcaQuery wmca_query_ = nullptr;

    bool create_message_window();
    void destroy_message_window();
    bool resolve_symbols();
    bool wait_for_connected(int timeout_ms, std::string& error_message);
#endif
};

#endif
