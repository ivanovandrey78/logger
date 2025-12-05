#pragma once 

#include <iostream>
#include <fstream>

enum OutType { CONSOLE, OUT_FILE };
enum LogLevel { DEBUG, INFO, WARN, ERROR };

class Logger {
private:
    LogLevel cur_level_ = LogLevel::INFO;  // defalut value
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
    static void log(LogLevel level, const std::string& message);

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
    void write(const std::string& message);
};