#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

class Logger {
public:
    explicit Logger(const std::string& file_path, bool mirror_stdout = true);
    ~Logger();

    void info(const std::string& message);
    void warn(const std::string& message);
    void error(const std::string& message);

private:
    std::ofstream stream_;
    bool mirror_stdout_ = true;
    void write(const std::string& level, const std::string& message);
};

#endif
