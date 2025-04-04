#pragma once

#include <format>
#include <iostream>
#include <string>
#include <source_location>

enum class LoggingLevel { INFO, WARN, ERROR };

class Logger {
public:
    static void info(
        const std::string_view message,
        const std::source_location location = std::source_location::current());
    static void warn(
        const std::string_view message,
        const std::source_location location = std::source_location::current());
    static void error(
        const std::string_view message,
        const std::source_location location = std::source_location::current());

private:
    static void log(LoggingLevel level, 
                    const std::string_view message,
                    const std::source_location location);
    static void log_time();
};
