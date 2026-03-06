#include "qv_auth.h"

#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

#include "qv_protocol.h"

#ifdef _WIN32
#include <windows.h>
#endif

namespace {
std::string env_or_empty(const char* key) {
    const char* value = std::getenv(key);
    if (value == nullptr) {
        return "";
    }
    return std::string(value);
}

[[maybe_unused]] std::string trim(const std::string& input) {
    std::size_t start = 0;
    while (start < input.size() && std::isspace(static_cast<unsigned char>(input[start])) != 0) {
        ++start;
    }

    std::size_t end = input.size();
    while (end > start && std::isspace(static_cast<unsigned char>(input[end - 1])) != 0) {
        --end;
    }

    return input.substr(start, end - start);
}

std::string mask_account(const std::string& account_no) {
    if (account_no.size() <= 4) {
        return "****";
    }
    return std::string(account_no.size() - 4, '*') + account_no.substr(account_no.size() - 4);
}

#ifdef _WIN32
[[maybe_unused]] std::string prompt_line(const std::string& prompt) {
    std::cout << prompt << std::flush;
    std::string out;
    std::getline(std::cin, out);
    return trim(out);
}

[[maybe_unused]] int env_to_int(const char* key, int default_value) {
    const std::string raw = env_or_empty(key);
    if (raw.empty()) {
        return default_value;
    }
    try {
        return std::stoi(raw);
    } catch (...) {
        return default_value;
    }
}

[[maybe_unused]] char env_to_char(const char* key, char default_value) {
    const std::string raw = env_or_empty(key);
    if (raw.empty()) {
        return default_value;
    }
    return raw.front();
}

struct LoginDialogState {
    std::string id;
    std::string password;
    std::string cert_password;
    bool accepted = false;
};

constexpr int IDC_EDIT_ID = 1001;
constexpr int IDC_EDIT_PASSWORD = 1002;
constexpr int IDC_EDIT_CERT_PASSWORD = 1003;

std::wstring utf8_to_wide(const std::string& input) {
    if (input.empty()) {
        return L"";
    }

    const int wide_len = MultiByteToWideChar(CP_UTF8, 0, input.c_str(), -1, nullptr, 0);
    if (wide_len <= 0) {
        return L"";
    }

    std::wstring wide;
    wide.resize(static_cast<std::size_t>(wide_len));
    MultiByteToWideChar(CP_UTF8, 0, input.c_str(), -1, wide.data(), wide_len);
    if (!wide.empty() && wide.back() == L'\0') {
        wide.pop_back();
    }
    return wide;
}

std::string wide_to_utf8(const std::wstring& input) {
    if (input.empty()) {
        return "";
    }

    const int utf8_len = WideCharToMultiByte(CP_UTF8, 0, input.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (utf8_len <= 0) {
        return "";
    }

    std::string utf8;
    utf8.resize(static_cast<std::size_t>(utf8_len));
    WideCharToMultiByte(CP_UTF8, 0, input.c_str(), -1, utf8.data(), utf8_len, nullptr, nullptr);
    if (!utf8.empty() && utf8.back() == '\0') {
        utf8.pop_back();
    }
    return utf8;
}

std::wstring get_control_text(HWND hwnd, int control_id) {
    HWND control = GetDlgItem(hwnd, control_id);
    if (control == nullptr) {
        return L"";
    }

    const int length = GetWindowTextLengthW(control);
    std::wstring text;
    text.resize(static_cast<std::size_t>(length + 1));
    GetWindowTextW(control, text.data(), length + 1);
    if (!text.empty() && text.back() == L'\0') {
        text.pop_back();
    }
    return text;
}

void set_default_font(HWND hwnd) {
    SendMessageW(hwnd, WM_SETFONT, reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), TRUE);
}

void center_window(HWND hwnd) {
    RECT rect{};
    if (GetWindowRect(hwnd, &rect) == 0) {
        return;
    }

    const int width = rect.right - rect.left;
    const int height = rect.bottom - rect.top;
    const int screen_width = GetSystemMetrics(SM_CXSCREEN);
    const int screen_height = GetSystemMetrics(SM_CYSCREEN);
    const int x = std::max(0, (screen_width - width) / 2);
    const int y = std::max(0, (screen_height - height) / 2);
    SetWindowPos(hwnd, nullptr, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

HWND create_dialog_control(DWORD ex_style,
                           const wchar_t* class_name,
                           const wchar_t* text,
                           DWORD style,
                           int x,
                           int y,
                           int width,
                           int height,
                           HWND parent,
                           int control_id) {
    HWND control = CreateWindowExW(
        ex_style,
        class_name,
        text,
        style,
        x,
        y,
        width,
        height,
        parent,
        reinterpret_cast<HMENU>(static_cast<INT_PTR>(control_id)),
        GetModuleHandleW(nullptr),
        nullptr);
    if (control != nullptr) {
        set_default_font(control);
    }
    return control;
}

INT_PTR CALLBACK login_dialog_proc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param) {
    switch (message) {
        case WM_INITDIALOG: {
            auto* state = reinterpret_cast<LoginDialogState*>(l_param);
            SetWindowLongPtrW(hwnd, DWLP_USER, l_param);
            SetWindowTextW(hwnd, L"NH QV 로그인");

            create_dialog_control(0, L"STATIC", L"QV ID", WS_CHILD | WS_VISIBLE, 16, 16, 100, 20, hwnd, -1);
            HWND id_edit = create_dialog_control(
                WS_EX_CLIENTEDGE,
                L"EDIT",
                utf8_to_wide(state->id).c_str(),
                WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL,
                16,
                34,
                268,
                24,
                hwnd,
                IDC_EDIT_ID);

            create_dialog_control(0, L"STATIC", L"계좌 비밀번호", WS_CHILD | WS_VISIBLE, 16, 66, 100, 20, hwnd, -1);
            create_dialog_control(
                WS_EX_CLIENTEDGE,
                L"EDIT",
                utf8_to_wide(state->password).c_str(),
                WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | ES_PASSWORD,
                16,
                84,
                268,
                24,
                hwnd,
                IDC_EDIT_PASSWORD);

            create_dialog_control(0, L"STATIC", L"인증서 비밀번호", WS_CHILD | WS_VISIBLE, 16, 116, 120, 20, hwnd, -1);
            create_dialog_control(
                WS_EX_CLIENTEDGE,
                L"EDIT",
                utf8_to_wide(state->cert_password).c_str(),
                WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL | ES_PASSWORD,
                16,
                134,
                268,
                24,
                hwnd,
                IDC_EDIT_CERT_PASSWORD);

            create_dialog_control(
                0,
                L"BUTTON",
                L"확인",
                WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
                128,
                174,
                72,
                26,
                hwnd,
                IDOK);
            create_dialog_control(
                0,
                L"BUTTON",
                L"취소",
                WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON,
                212,
                174,
                72,
                26,
                hwnd,
                IDCANCEL);

            center_window(hwnd);
            if (id_edit != nullptr) {
                SetFocus(id_edit);
            }
            return FALSE;
        }
        case WM_COMMAND: {
            const int command = LOWORD(w_param);
            if (command == IDOK) {
                auto* state = reinterpret_cast<LoginDialogState*>(GetWindowLongPtrW(hwnd, DWLP_USER));
                if (state != nullptr) {
                    state->id = trim(wide_to_utf8(get_control_text(hwnd, IDC_EDIT_ID)));
                    state->password = trim(wide_to_utf8(get_control_text(hwnd, IDC_EDIT_PASSWORD)));
                    state->cert_password = trim(wide_to_utf8(get_control_text(hwnd, IDC_EDIT_CERT_PASSWORD)));
                    state->accepted = true;
                }
                EndDialog(hwnd, IDOK);
                return TRUE;
            }
            if (command == IDCANCEL) {
                EndDialog(hwnd, IDCANCEL);
                return TRUE;
            }
            break;
        }
        case WM_CLOSE:
            EndDialog(hwnd, IDCANCEL);
            return TRUE;
        default:
            break;
    }
    return FALSE;
}

bool prompt_windows_credentials(LoginDialogState& state) {
    alignas(DLGTEMPLATE) unsigned char buffer[sizeof(DLGTEMPLATE) + sizeof(WORD) * 3] = {};
    auto* dialog = reinterpret_cast<DLGTEMPLATE*>(buffer);
    dialog->style = WS_POPUP | WS_CAPTION | WS_SYSMENU | DS_MODALFRAME;
    dialog->dwExtendedStyle = 0;
    dialog->cdit = 0;
    dialog->x = 10;
    dialog->y = 10;
    dialog->cx = 300;
    dialog->cy = 215;

    WORD* words = reinterpret_cast<WORD*>(buffer + sizeof(DLGTEMPLATE));
    words[0] = 0;
    words[1] = 0;
    words[2] = 0;

    const INT_PTR result = DialogBoxIndirectParamW(
        GetModuleHandleW(nullptr),
        dialog,
        nullptr,
        login_dialog_proc,
        reinterpret_cast<LPARAM>(&state));

    return result == IDOK && state.accepted;
}
#endif

#ifdef _WIN32
std::string cp949_to_utf8(const char* input, int length) {
    if (input == nullptr || length <= 0) {
        return "";
    }

    int wide_len = MultiByteToWideChar(949, 0, input, length, nullptr, 0);
    if (wide_len <= 0) {
        return std::string(input, input + length);
    }

    std::wstring wide;
    wide.resize(static_cast<std::size_t>(wide_len));
    MultiByteToWideChar(949, 0, input, length, wide.data(), wide_len);

    int utf8_len = WideCharToMultiByte(CP_UTF8, 0, wide.data(), wide_len, nullptr, 0, nullptr, nullptr);
    if (utf8_len <= 0) {
        return std::string(input, input + length);
    }

    std::string utf8;
    utf8.resize(static_cast<std::size_t>(utf8_len));
    WideCharToMultiByte(CP_UTF8, 0, wide.data(), wide_len, utf8.data(), utf8_len, nullptr, nullptr);
    return utf8;
}

std::string fixed_cp949_field(const char* field, int size) {
    int used = size;
    while (used > 0) {
        const char ch = field[used - 1];
        if (ch == '\0' || ch == ' ') {
            --used;
            continue;
        }
        break;
    }
    return trim(cp949_to_utf8(field, used));
}

std::string cstr_cp949(const char* cstr) {
    if (cstr == nullptr) {
        return "";
    }
    return trim(cp949_to_utf8(cstr, static_cast<int>(std::strlen(cstr))));
}

struct QVEventEntry {
    std::uint32_t code;
    std::intptr_t lparam;
};

std::vector<QVEventEntry> g_event_queue;

LRESULT CALLBACK qv_wnd_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    if (msg == WM_WMCAEVENT) {
        g_event_queue.push_back({static_cast<std::uint32_t>(wparam), static_cast<std::intptr_t>(lparam)});
        return 0;
    }
    return DefWindowProcA(hwnd, msg, wparam, lparam);
}
#endif
}  // namespace

QVAuth::QVAuth(Logger& logger) : logger_(logger) {}

QVAuth::~QVAuth() {
#ifdef _WIN32
    if (!mock_mode_) {
        if (wmca_disconnect_ != nullptr) {
            wmca_disconnect_();
        }
        destroy_message_window();
        if (wmca_free_ != nullptr) {
            wmca_free_();
        }
    }

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
        account_no_ = "1234567890";
        account_index_ = 1;
        logger_.warn("QV_MOCK=1 enabled. fetch.exe runs in mock mode.");
        return true;
    }

#ifdef _WIN32
    const std::string custom_dll = env_or_empty("QV_DLL_PATH");
    const std::vector<std::string> candidates = custom_dll.empty()
        ? std::vector<std::string>{
              "wmca.dll",
              "cpp\\lib\\wmca.dll",
              "..\\lib\\wmca.dll",
          }
        : std::vector<std::string>{custom_dll};

    for (const auto& path : candidates) {
        HMODULE handle = LoadLibraryA(path.c_str());
        if (handle != nullptr) {
            dll_handle_ = reinterpret_cast<void*>(handle);
            logger_.info("Loaded QV DLL from: " + path);
            break;
        }
    }

    if (dll_handle_ == nullptr) {
        logger_.error("Failed to load wmca.dll. Install QV Open API and configure QV_DLL_PATH if needed.");
        return false;
    }

    if (!resolve_symbols()) {
        return false;
    }

    if (wmca_load_ != nullptr) {
        const int ret = wmca_load_();
        logger_.info("wmcaLoad return code=" + std::to_string(ret));
    }

    if (!create_message_window()) {
        return false;
    }

    return true;
#else
    logger_.error("QV DLL loading is supported only on Windows.");
    return false;
#endif
}

bool QVAuth::login() {
    if (mock_mode_) {
        return true;
    }

#ifdef _WIN32
    std::string id = trim(env_or_empty("QV_ID"));
    std::string password = trim(env_or_empty("QV_PASSWORD"));
    std::string cert_password = trim(env_or_empty("QV_CERT_PASSWORD"));

    if (id.empty() || password.empty() || cert_password.empty()) {
        LoginDialogState dialog_state{id, password, cert_password, false};
        if (prompt_windows_credentials(dialog_state)) {
            id = dialog_state.id;
            password = dialog_state.password;
            cert_password = dialog_state.cert_password;
        } else {
            if (id.empty()) {
                id = prompt_line("Enter QV ID: ");
            }
            if (password.empty()) {
                password = prompt_line("Enter QV account password: ");
            }
            if (cert_password.empty()) {
                cert_password = prompt_line("Enter certificate password: ");
            }
        }
    }

    if (id.empty() || password.empty() || cert_password.empty()) {
        logger_.error("ID/password/certificate password is required.");
        return false;
    }

    const char media_type = env_to_char("QV_MEDIA_TYPE", 'P');
    const char user_type = env_to_char("QV_USER_TYPE", '1');

    if (wmca_connect_ == nullptr || hwnd_ == nullptr) {
        logger_.error("wmcaConnect is not initialized.");
        return false;
    }

    const int ret = wmca_connect_(
        hwnd_,
        static_cast<unsigned long>(WM_WMCAEVENT),
        media_type,
        user_type,
        id.c_str(),
        password.c_str(),
        cert_password.c_str());
    logger_.info("wmcaConnect return code=" + std::to_string(ret));

    std::string error_message;
    if (!wait_for_connected(env_to_int("QV_LOGIN_TIMEOUT_MS", 30000), error_message)) {
        logger_.error("QV login failed: " + error_message);
        return false;
    }

    logger_.info("QV login succeeded. account=" + masked_account() + " account_index=" + std::to_string(account_index_));
    return true;
#else
    logger_.error("QV login is supported only on Windows.");
    return false;
#endif
}

bool QVAuth::submit_query(int tr_index,
                          const std::string& tr_code,
                          const void* input,
                          int input_size) const {
    if (mock_mode_) {
        return false;
    }

#ifdef _WIN32
    if (wmca_query_ == nullptr || hwnd_ == nullptr) {
        logger_.error("wmcaQuery is not initialized.");
        return false;
    }

    const int ret = wmca_query_(
        hwnd_,
        tr_index,
        tr_code.c_str(),
        reinterpret_cast<const char*>(input),
        input_size,
        account_index_);

    if (ret == 0) {
        logger_.warn("wmcaQuery returned 0 for tr_code=" + tr_code + " (will wait for async event).");
    }

    return true;
#else
    (void)tr_index;
    (void)tr_code;
    (void)input;
    (void)input_size;
    return false;
#endif
}

bool QVAuth::wait_for_event(QVEvent& event, int timeout_ms, std::string& error_message) const {
    if (mock_mode_) {
        error_message = "mock mode";
        return false;
    }

#ifdef _WIN32
    const auto start = std::chrono::steady_clock::now();

    while (true) {
        // Pump messages so SendMessage-based events reach qv_wnd_proc
        MSG msg{};
        while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE) != 0) {
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }

        // Check events captured by qv_wnd_proc
        if (!g_event_queue.empty()) {
            const auto& entry = g_event_queue.front();
            event.code = entry.code;
            event.lparam = entry.lparam;
            g_event_queue.erase(g_event_queue.begin());
            return true;
        }

        const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - start);
        if (elapsed.count() >= timeout_ms) {
            std::ostringstream oss;
            oss << "timeout waiting WM_WMCAEVENT (" << timeout_ms << "ms)";
            error_message = oss.str();
            return false;
        }

        Sleep(10);
    }
#else
    (void)event;
    (void)timeout_ms;
    error_message = "not supported on non-Windows";
    return false;
#endif
}

std::string QVAuth::masked_account() const {
    return mask_account(account_no_.empty() ? "0000000000" : account_no_);
}

int QVAuth::account_index() const {
    return account_index_;
}

bool QVAuth::is_mock_mode() const {
    return mock_mode_;
}

#ifdef _WIN32
bool QVAuth::create_message_window() {
    if (hwnd_ != nullptr) {
        return true;
    }

    HINSTANCE instance = GetModuleHandleA(nullptr);
    if (instance == nullptr) {
        logger_.error("GetModuleHandleA failed while creating message window.");
        return false;
    }

    const char* class_name = "QVFetchMessageWindow";
    WNDCLASSA wc{};
    wc.lpfnWndProc = qv_wnd_proc;
    wc.hInstance = instance;
    wc.lpszClassName = class_name;

    const ATOM atom = RegisterClassA(&wc);
    if (atom == 0 && GetLastError() != ERROR_CLASS_ALREADY_EXISTS) {
        logger_.error("RegisterClassA failed for QV message window.");
        return false;
    }

    HWND hwnd = CreateWindowExA(
        0,
        class_name,
        "QVFetchHidden",
        0,
        0,
        0,
        0,
        0,
        HWND_MESSAGE,
        nullptr,
        instance,
        nullptr);

    if (hwnd == nullptr) {
        logger_.error("CreateWindowExA failed for QV message window.");
        return false;
    }

    hwnd_ = reinterpret_cast<void*>(hwnd);
    return true;
}

void QVAuth::destroy_message_window() {
    if (hwnd_ == nullptr) {
        return;
    }

    DestroyWindow(reinterpret_cast<HWND>(hwnd_));
    hwnd_ = nullptr;
}

bool QVAuth::resolve_symbols() {
    if (dll_handle_ == nullptr) {
        logger_.error("DLL handle is null when resolving symbols.");
        return false;
    }

    const auto load_symbol = [&](const char* name, auto& out_fn) -> bool {
        out_fn = reinterpret_cast<std::remove_reference_t<decltype(out_fn)>>(GetProcAddress(
            reinterpret_cast<HMODULE>(dll_handle_),
            name));
        if (out_fn == nullptr) {
            logger_.error(std::string("GetProcAddress failed: ") + name);
            return false;
        }
        return true;
    };

    return load_symbol("wmcaLoad", wmca_load_) &&
           load_symbol("wmcaFree", wmca_free_) &&
           load_symbol("wmcaConnect", wmca_connect_) &&
           load_symbol("wmcaDisconnect", wmca_disconnect_) &&
           load_symbol("wmcaQuery", wmca_query_);
}

bool QVAuth::wait_for_connected(int timeout_ms, std::string& error_message) {
    const auto start = std::chrono::steady_clock::now();

    while (true) {
        QVEvent event;
        std::string wait_error;
        const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - start);
        const int remain = timeout_ms - static_cast<int>(elapsed.count());
        if (remain <= 0) {
            error_message = "login timeout";
            return false;
        }

        if (!wait_for_event(event, std::min(remain, 1000), wait_error)) {
            if (wait_error.rfind("timeout", 0) == 0) {
                continue;
            }
            error_message = wait_error;
            return false;
        }

        if (event.code == CA_CONNECTED) {
            const auto* login_block = reinterpret_cast<const LoginBlock*>(event.lparam);
            if (login_block == nullptr || login_block->login_info == nullptr) {
                error_message = "connected event missing login info";
                return false;
            }

            const LoginInfo* info = login_block->login_info;
            int account_count = 0;
            try {
                account_count = std::stoi(fixed_cp949_field(info->account_count, static_cast<int>(sizeof(info->account_count))));
            } catch (...) {
                account_count = 0;
            }

            account_index_ = env_to_int("QV_ACCOUNT_INDEX", 1);
            if (account_index_ <= 0) {
                account_index_ = 1;
            }

            int selected = account_index_ - 1;
            if (account_count > 0) {
                selected = std::clamp(selected, 0, account_count - 1);
                account_no_ = fixed_cp949_field(
                    info->account_infoes[selected].account_no,
                    static_cast<int>(sizeof(info->account_infoes[selected].account_no)));
                account_index_ = selected + 1;
            } else {
                account_no_ = "0000000000";
            }

            return true;
        }

        if (event.code == CA_RECEIVEMESSAGE) {
            const auto* out = reinterpret_cast<const OutDataBlock<MessageHeader>*>(event.lparam);
            if (out != nullptr && out->p_data != nullptr && out->p_data->sz_data != nullptr) {
                const MessageHeader* header = out->p_data->sz_data;
                const std::string code = fixed_cp949_field(header->message_code, static_cast<int>(sizeof(header->message_code)));
                const std::string msg = fixed_cp949_field(header->message, static_cast<int>(sizeof(header->message)));
                logger_.info("Login message [" + code + "] " + msg);
            }
            continue;
        }

        if (event.code == CA_RECEIVEERROR) {
            const auto* out = reinterpret_cast<const OutDataBlock<char>*>(event.lparam);
            if (out != nullptr && out->p_data != nullptr && out->p_data->sz_data != nullptr) {
                error_message = cstr_cp949(out->p_data->sz_data);
            } else {
                error_message = "receive error";
            }
            return false;
        }

        if (event.code == CA_DISCONNECTED || event.code == CA_SOCKETERROR) {
            error_message = "disconnected during login";
            return false;
        }
    }
}
#endif
