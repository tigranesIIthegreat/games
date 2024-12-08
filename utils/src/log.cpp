#include "log.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

Logger& Logger::instance() {
    static auto instance = Logger();
    return instance;
}

void Logger::log(LoggingLevel level, const char* format, ...) {
#if defined(DEBUG)
    va_list args;
    va_start(args, format);
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);

    log_time();
    static std::string default_setting = "\e[0;37m";
    static std::string intro[] = {
        "\e[0;37mINF: ",  // INFO
        "\e[1;33mWRN: ",  // WARN
        "\e[1;31mERR: "   // ERROR
    };

    std::cout << intro[static_cast<size_t>(level)] << buffer 
              << default_setting << std::endl;

    va_end(args);
#else
    (void)level;
    (void)message;
#endif
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