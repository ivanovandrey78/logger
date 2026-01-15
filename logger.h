#pragma once

#include <iostream>
#include <fstream>
#include <string>

enum class LogLevel { DEBUG, INFO, WARN, ERROR };

class Logger {
public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger& getInstance();

    static void SetLevel(LogLevel level);
    static void SetConsoleOutput();
    static void SetFileOutput(const std::string& filename);

    static void Debug(const std::string& message);
    static void Info(const std::string& message);
    static void Warn(const std::string& message);
    static void Error(const std::string& message);

    static void Log(LogLevel level, const std::string& message);

private:
    Logger() = default;
    ~Logger();

    bool ShouldLog(LogLevel level) const;
    void Write(LogLevel level, const std::string& message);
    const char* LevelToString(LogLevel level) const;

    LogLevel current_level_ = LogLevel::INFO;
    std::ostream* output_ = &std::cerr;
    std::ofstream file_stream_;
};