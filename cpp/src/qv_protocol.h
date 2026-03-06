#ifndef QV_PROTOCOL_H
#define QV_PROTOCOL_H

#include <cstdint>

#ifdef _WIN32
#include <windows.h>
#else
constexpr std::uint32_t WM_USER = 0x0400;
#endif

constexpr std::uint32_t WM_WMCAEVENT = WM_USER + 8400;
constexpr std::uint32_t CA_CONNECTED = WM_USER + 110;
constexpr std::uint32_t CA_DISCONNECTED = WM_USER + 120;
constexpr std::uint32_t CA_SOCKETERROR = WM_USER + 130;
constexpr std::uint32_t CA_RECEIVEDATA = WM_USER + 210;
constexpr std::uint32_t CA_RECEIVESISE = WM_USER + 220;
constexpr std::uint32_t CA_RECEIVEMESSAGE = WM_USER + 230;
constexpr std::uint32_t CA_RECEIVECOMPLETE = WM_USER + 240;
constexpr std::uint32_t CA_RECEIVEERROR = WM_USER + 250;

struct MessageHeader {
    char message_code[5];
    char message[80];
};

template <typename T>
struct ReceivedData {
    const char* block_name;
    const T* sz_data;
    int len;
};

template <typename T>
struct OutDataBlock {
    int tr_index;
    const ReceivedData<T>* p_data;
};

struct AccountInfo {
    char account_no[11];
    char account_name[40];
    char act_pdt_cdz3[3];
    char amn_tab_cdz4[4];
    char expr_datez8[8];
    char granted;
    char filler[189];
};

struct LoginInfo {
    char login_datetime[14];
    char server_name[15];
    char user_id[8];
    char account_count[3];
    AccountInfo account_infoes[999];
};

struct LoginBlock {
    int tr_index;
    const LoginInfo* login_info;
};

#endif
