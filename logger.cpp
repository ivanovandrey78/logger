#include "logger.h"

#include <string>
#include <chrono>
#include <cstring>
#include <iomanip>

// Log function 
void Logger::log(LogLevel level, const std::string& message) {
    auto& logger = getInstance();
    if (logger.shouldLog(level)) {
        logger.write(message);
    }
}

// Write smth in output 
void Logger::write(const std::string& message) {
    if (output_) {
        auto const now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        *output_ << std::put_time(std::localtime(&time),"%H:%M:%S");
        *output_ << ' ' << message << std::endl;
    }
}