#pragma once 

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

enum OutType { CONSOLE, FILE };
enum LogLevel { DEBUG, INFO, WARN, ERROR };

class Logger {
private:
    LogLevel cur_level_ = LogLevel::INFO; // defalut value
    std::ostream* output_ = &std::cerr;    // defalut stream

public: 
    // Prohibition on copying
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete; 

    // Logger settings
    static void setLevel(LogLevel level) {
        getInstance().cur_level_ = level;
    }
    
    static void setOutput(std::ostream& os) {
        getInstance().output_ = &os;
    }

    // Main log func
    static void log(LogLevel level, const std::string& message) {
        auto& logger = getInstance();
        if (logger.shouldLog(level)) {
            logger.write(message);
        }
    }

private: 
    // Logger on - SingleTone Init
    static Logger& getInstance() {
        static Logger logger;
        return logger;
    }

    // Default constructor
    Logger() = default;

    // Checking that a event is worth logging
    bool shouldLog(LogLevel level) const {
        return level >= cur_level_;
    }
    
    /// Write in smth output
    void write(const std::string& message) {
        if (output_) {
            *output_ << message << std::endl;
        }
    }
};

#define LOG_DEBUG(msg) Logger::log(LogLevel::DEBUG, msg)
#define LOG_INFO(msg)  Logger::log(LogLevel::INFO, msg)
#define LOG_WARN(msg)  Logger::log(LogLevel::WARNING, msg)
#define LOG_ERROR(msg) Logger::log(LogLevel::ERROR, msg)