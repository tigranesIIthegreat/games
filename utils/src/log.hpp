#pragma once

#include <iostream>
#include <string>

enum class LoggingLevel { INFO, WARN, ERROR };

class Logger {
public:
    static Logger& instance();

    void info(const std::string& message);
    void warn(const std::string& message);
    void error(const std::string& message);

private:
    Logger() = default;

private:
    void log(LoggingLevel level, const std::string& message);
    void log_time();
};