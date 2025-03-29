#pragma once

#include <iostream>
#include <string>

enum class LoggingLevel { INFO, WARN, ERROR };

class Logger {
public:
    template <typename... Args>
    static void info(const char* format, Args&&... args);

    template <typename... Args>
    static void warn(const char* format, Args&&... args);

    template <typename... Args>
    static void error(const char* format, Args&&... args);

private:
    static void log(LoggingLevel level, const char* format, ...);
    static void log_time();
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