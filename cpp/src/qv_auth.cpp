#include "qv_auth.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

namespace {
std::string mask_account(const std::string& account_no) {
    if (account_no.size() <= 4) {
        return "****";
    }
    return std::string(account_no.size() - 4, '*') + account_no.substr(account_no.size() - 4);
}

std::string env_or_empty(const char* key) {
    const char* value = std::getenv(key);
    if (value == nullptr) {
        return "";
    }
    return std::string(value);
}
}  // namespace

QVAuth::QVAuth(Logger& logger) : logger_(logger) {}

QVAuth::~QVAuth() {
#ifdef _WIN32
    if (dll_handle_ != nullptr) {
        FreeLibrary(reinterpret_cast<HMODULE>(dll_handle_));
        dll_handle_ = nullptr;
    }
#endif
}

bool QVAuth::load_dll() {
    const std::string mock = env_or_empty("QV_MOCK");
    if (mock == "1") {
        mock_mode_ = true;
        logger_.warn("QV_MOCK=1 enabled. fetch.exe runs in mock mode.");
        return true;
    }

#ifdef _WIN32
    const std::vector<std::string> candidates = {
        "wmca.dll",
        "cpp\\lib\\wmca.dll",
        "..\\lib\\wmca.dll"
    };

    for (const auto& path : candidates) {
        HMODULE handle = LoadLibraryA(path.c_str());
        if (handle != nullptr) {
            dll_handle_ = reinterpret_cast<void*>(handle);
            logger_.info("Loaded QV DLL from: " + path);
            return true;
        }
    }

    logger_.error("Failed to load wmca.dll. Install QV Open API and place DLL in cpp/lib.");
    return false;
#else
    logger_.error("QV DLL loading is supported only on Windows.");
    return false;
#endif
}

bool QVAuth::login() {
    if (mock_mode_) {
        account_no_ = "1234567890";
        return true;
    }

    // NOTE: Actual NH QV login binding must be integrated with the vendor API signatures.
    // Password is intentionally not persisted.
    std::string password = env_or_empty("QV_CERT_PASSWORD");
    if (password.empty()) {
        std::cout << "Enter certificate password: " << std::flush;
        std::getline(std::cin, password);
    }
    if (password.empty()) {
        logger_.error("Certificate password is empty. Manual password input is required.");
        return false;
    }

    logger_.error("QV login binding not linked yet. Wire wmca.dll login function in qv_auth.cpp.");
    return false;
}

std::string QVAuth::masked_account() const {
    return mask_account(account_no_.empty() ? "0000000000" : account_no_);
}

bool QVAuth::is_mock_mode() const {
    return mock_mode_;
}
