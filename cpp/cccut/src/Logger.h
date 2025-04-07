//
// Created by pbarbeira on 06-04-2025.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <memory>
#include <vector>
#include <chrono>

enum class LogLevel{
    ERROR, WARNING, INFO, DEBUG
};

struct Log{
    LogLevel level;
    time_t timestamp;
    std::string message;
};

class Logger{
    std::vector<std::unique_ptr<Log>> _logs;

    static std::string _buildLogMessage(const Log* log) {
        auto logTime = std::put_time(std::localtime(&log->timestamp), "%Y-%m-%d %H:%M:%S");
        std::string logLevel;
        switch (log->level) {
            case LogLevel::ERROR: logLevel = "ERROR"; break;
            case LogLevel::WARNING: logLevel = "WARNING"; break;
            case LogLevel::INFO: logLevel = "INFO"; break;
            case LogLevel::DEBUG: logLevel = "DEBUG"; break;
            default: throw std::runtime_error("Unknown log level");
        }
        std::stringstream ss;
        ss << "[" << logTime << "] - [" << logLevel << "]::" << log->message << "\n";
        return ss.str();
    }

    public:
        void log(LogLevel level, const std::string& message){
            auto log = std::make_unique<Log>();
            log->level = level;
            log->message = message;
            log->timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            _logs.push_back(std::move(log));
        }

        std::vector<std::unique_ptr<Log>> getLogs(bool flush = false){
            auto logs = std::move(_logs);
            if (flush) {
                _logs.clear();
            }
            return std::move(logs);
        }

        void print(std::ostream& out, bool flush = false) {
            for (const auto& log : _logs) {
                out << _buildLogMessage(log.get());
            }
            if (flush){
                _logs.clear();
            }
        }
};

#endif //LOGGER_H
