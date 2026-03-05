#include "logger.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace {
std::string now_string() {
    const auto now = std::chrono::system_clock::now();
    const std::time_t time_now = std::chrono::system_clock::to_time_t(now);
    std::tm tm_now{};
#ifdef _WIN32
    localtime_s(&tm_now, &time_now);
#else
    localtime_r(&time_now, &tm_now);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm_now, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}
}  // namespace

Logger::Logger(const std::string& file_path) {
    stream_.open(file_path, std::ios::app);
}

Logger::~Logger() {
    if (stream_.is_open()) {
        stream_.flush();
        stream_.close();
    }
}

void Logger::info(const std::string& message) {
    write("INFO", message);
}

void Logger::warn(const std::string& message) {
    write("WARN", message);
}

void Logger::error(const std::string& message) {
    write("ERROR", message);
}

void Logger::write(const std::string& level, const std::string& message) {
    const std::string line = "[" + now_string() + "] [" + level + "] " + message;
    std::cout << line << std::endl;
    if (stream_.is_open()) {
        stream_ << line << '\n';
        stream_.flush();
    }
}
