#include <utils/log.hpp>

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

using namespace std::chrono;

void Logger::info(const std::string_view message,
                  const std::source_location location) {
    log(LoggingLevel::INFO, message, location);
}

void Logger::warn(const std::string_view message,
                  const std::source_location location) {
    log(LoggingLevel::WARN, message, location);
}

void Logger::error(const std::string_view message,
                   const std::source_location location) {
    log(LoggingLevel::ERROR, message, location);
}

void Logger::log(LoggingLevel level, 
                 const std::string_view message,
                 const std::source_location location) {
    static std::string intro[] = {
        "\e[0;37m[INF] ",  // INFO
        "\e[1;33m[WRN] ",  // WARN
        "\e[1;31m[ERR] "   // ERROR
    };
    log_time();
    static std::string default_setting = "\e[0;37m";
    std::clog << intro[static_cast<int>(level)] 
              << location.file_name() << ':'
              << location.line() << " " 
              << message << '\n' << default_setting;
}

void Logger::log_time() {
    auto now = system_clock::now();
    std::time_t now_c = system_clock::to_time_t(now);
    auto localTime = *std::localtime(&now_c);
    auto duration = now.time_since_epoch();
    auto millis = duration_cast<milliseconds>(duration).count() % 1000;

    std::clog << "\e[0;36m"
              << std::put_time(&localTime, "[%H:%M:%S") << "."
              << std::setfill('0') << std::setw(3) << millis << "] "
              << "\e[0;37m";
}