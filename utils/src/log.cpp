#include "log.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

Logger& Logger::instance() {
    static auto instance = Logger();
    return instance;
}

void Logger::info(const std::string& message) {
    log(LoggingLevel::INFO, message);
}

void Logger::warn(const std::string& message) {
    log(LoggingLevel::WARN, message);
}

void Logger::error(const std::string& message) {
    log(LoggingLevel::ERROR, message);
}

void Logger::log(LoggingLevel level, const std::string& message) {
    log_time();
    static std::string default_setting = "\e[0;37m";
    static std::string intro[] = {
        "\e[0;37mINF: ",  // INFO
        "\e[1;33mWRN: ",  // WARN
        "\e[1;31mERR: "   // ERROR
    };

    std::cout << intro[static_cast<size_t>(level)] << message
              << default_setting << std::endl;
}

void Logger::log_time() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    auto localTime = *std::localtime(&now_c);
    auto duration = now.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() % 1000;

    std::cout << std::put_time(&localTime, "[%H:%M:%S") << "."
              << std::setfill('0') << std::setw(3) << millis << "] ";
}