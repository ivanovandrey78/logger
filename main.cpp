#include "logger.h"

int main() {
    Logger::SetLevel(LogLevel::DEBUG);

    Logger::Debug("Application started");
    Logger::Info("Initializing modules...");
    Logger::Warn("Config file not found, using defaults");
    Logger::Error("Failed to connect to database");

    Logger::SetFileOutput("app.log");

    Logger::Info("Switched to file logging");
    Logger::Debug("Processing data...");
    Logger::Error("Critical error occurred");

    Logger::SetConsoleOutput();
    Logger::Info("Back to console output");

    Logger::SetLevel(LogLevel::WARN);
    Logger::Debug("This won't be shown");
    Logger::Info("This won't be shown either");
    Logger::Warn("This will be shown");
    Logger::Error("This will be shown too");

    return 0;
}