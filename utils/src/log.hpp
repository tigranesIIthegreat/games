#pragma once

#include <iostream>
#include <string>

enum class LoggingLevel { INFO, WARN, ERROR };

class Logger {
public:
    static Logger& instance();

    template <typename... Args>
    void info(const char* format, Args&&... args);

    template <typename... Args>
    void warn(const char* format, Args&&... args);

    template <typename... Args>
    void error(const char* format, Args&&... args);
private:
    Logger() = default;

private:
    void log(LoggingLevel level, const char* format, ...);
    void log_time();
};

template <typename... Args>
void Logger::info(const char* format, Args&&... args) {
    log(LoggingLevel::INFO, format, std::forward<Args>(args)...);
}

template <typename... Args>
void Logger::warn(const char* format, Args&&... args) {
    log(LoggingLevel::WARN, format, std::forward<Args>(args)...);
}

template <typename... Args>
void Logger::error(const char* format, Args&&... args) {
    log(LoggingLevel::ERROR, format, std::forward<Args>(args)...);
}