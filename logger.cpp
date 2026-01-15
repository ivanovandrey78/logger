#include "logger.h"

#include <chrono>
#include <iomanip>

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

Logger::~Logger() {
    if (file_stream_.is_open()) {
        file_stream_.close();
    }
}

void Logger::SetLevel(LogLevel level) {
    getInstance().current_level_ = level;
}

void Logger::SetConsoleOutput() {
    auto& logger = getInstance();
    if (logger.file_stream_.is_open()) {
        logger.file_stream_.close();
    }
    logger.output_ = &std::cerr;
}

void Logger::SetFileOutput(const std::string& filename) {
    auto& logger = getInstance();
    if (logger.file_stream_.is_open()) {
        logger.file_stream_.close();
    }
    logger.file_stream_.open(filename, std::ios::app);
    if (logger.file_stream_.is_open()) {
        logger.output_ = &logger.file_stream_;
    }
}

void Logger::Debug(const std::string& message) {
    Log(LogLevel::DEBUG, message);
}

void Logger::Info(const std::string& message) {
    Log(LogLevel::INFO, message);
}

void Logger::Warn(const std::string& message) {
    Log(LogLevel::WARN, message);
}

void Logger::Error(const std::string& message) {
    Log(LogLevel::ERROR, message);
}

void Logger::Log(LogLevel level, const std::string& message) {
    auto& logger = getInstance();
    if (logger.ShouldLog(level)) {
        logger.Write(level, message);
    }
}

bool Logger::ShouldLog(LogLevel level) const {
    return level >= current_level_;
}

void Logger::Write(LogLevel level, const std::string& message) {
    if (!output_) {
        return;
    }

    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;

    *output_ << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S")
             << '.' << std::setfill('0') << std::setw(3) << ms.count()
             << " [" << LevelToString(level) << "] "
             << message << std::endl;
}

const char* Logger::LevelToString(LogLevel level) const {
    switch (level) {
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO:  return "INFO ";
        case LogLevel::WARN:  return "WARN ";
        case LogLevel::ERROR: return "ERROR";
        default:              return "UNKNOWN";
    }
}