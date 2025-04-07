//
// Created by pbarbeira on 06-04-2025.
//

#include <gtest/gtest.h>
#include "../src/Logger.h"
#include <regex>

//We test through the StringLogger API since it just a base wrapper to
//automatically accumulate logs in a stringstream.

//Used in CanPrintLogs to facilitate result verification
const std::regex errorPattern(R"(\[\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}\.\d{3}.\d{3}\] - \[ERROR\] Error message)");
const std::regex warningPattern(R"(\[\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}\.\d{3}.\d{3}\] - \[WARNING\] Warning message)");
const std::regex infoPattern(R"(\[\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}\.\d{3}.\d{3}\] - \[INFO\] Info message)");
const std::regex debugPattern(R"(\[\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}\.\d{3}.\d{3}\] - \[DEBUG\] Debug message)");


TEST(LoggerTest, CanGetLogs) {
    const auto logger = std::make_unique<StringLogger>();

    logger->log(ERROR, "Error message");
    logger->log(WARNING, "Warning message");
    logger->log(INFO, "Info message");
    logger->log(DEBUG, "Debug message");

    const auto logs = logger->getLogs();
    EXPECT_EQ(logs.size(), 4);
}

TEST(LoggerTest, CanGetLogsAndFlush) {
    const auto logger = std::make_unique<StringLogger>();

    logger->log(LogLevel::ERROR, "Error message");
    logger->log(LogLevel::WARNING, "Warning message");
    logger->log(LogLevel::INFO, "Info message");
    logger->log(LogLevel::DEBUG, "Debug message");

    auto logs = logger->getLogs(true);
    EXPECT_EQ(logs.size(), 4);

    logs = logger->getLogs();
    EXPECT_EQ(logs.empty(), true);
}

TEST(LoggerTest, LogLevelError){
    const std::string MESSAGE = "Error";
    const auto logger = std::make_unique<StringLogger>();
    logger->log(LogLevel::ERROR, MESSAGE);

    auto logs = logger->getLogs();
    EXPECT_EQ(logs.size(), 1);

    auto log = std::move(logs[0]);
    EXPECT_EQ(log->level, LogLevel::ERROR);
    EXPECT_EQ(log->message, MESSAGE);
}

TEST(LoggerTest, LogLevelWarning){
    const std::string MESSAGE = "Warning";
    const auto logger = std::make_unique<StringLogger>();
    logger->log(LogLevel::WARNING, MESSAGE);

    auto logs = logger->getLogs();
    EXPECT_EQ(logs.size(), 1);

    auto log = std::move(logs[0]);
    EXPECT_EQ(log->level, LogLevel::WARNING);
    EXPECT_EQ(log->message, MESSAGE);
}
TEST(LoggerTest, LogLevelInfo){
    const std::string MESSAGE = "Info";
    const auto logger = std::make_unique<StringLogger>();
    logger->log(LogLevel::INFO, MESSAGE);

    auto logs = logger->getLogs();
    EXPECT_EQ(logs.size(), 1);

    auto log = std::move(logs[0]);
    EXPECT_EQ(log->level, LogLevel::INFO);
    EXPECT_EQ(log->message, MESSAGE);
}

TEST(LoggerTest, LogLevelDebug){
    const std::string MESSAGE = "Debug";
    const auto logger = std::make_unique<StringLogger>();
    logger->log(LogLevel::DEBUG, MESSAGE);

    auto logs = logger->getLogs();
    EXPECT_EQ(logs.size(), 1);

    auto log = std::move(logs[0]);
    EXPECT_EQ(log->level, LogLevel::DEBUG);
    EXPECT_EQ(log->message, MESSAGE);
}

TEST(LoggerTest, MultiLogLevels){
    const std::string DEBUG_MESSAGE = "Debug";
    const std::string WARNING_MESSAGE = "Warning";
    const auto logger = std::make_unique<StringLogger>();
    logger->log(LogLevel::DEBUG, DEBUG_MESSAGE);
    logger->log(LogLevel::WARNING, WARNING_MESSAGE);

    auto logs = logger->getLogs();
    EXPECT_EQ(logs.size(), 2);

    auto log = std::move(logs[0]);
    EXPECT_EQ(log->level, LogLevel::DEBUG);
    EXPECT_EQ(log->message, DEBUG_MESSAGE);

    log = std::move(logs[1]);
    EXPECT_EQ(log->level, LogLevel::WARNING);
    EXPECT_EQ(log->message, WARNING_MESSAGE);

}

TEST(LoggerTest, CanLogToOstream){
    const std::string MESSAGE = "Debug message";
    const auto logger = std::make_unique<StringLogger>();

    logger->log(DEBUG, MESSAGE);

    std::string log = logger->dump();
    //we purposely remove final \n
    log = log.substr(0, log.size() - 1);
    EXPECT_EQ(std::regex_match(log, debugPattern), true);

    const auto logs = logger->getLogs();
    EXPECT_EQ(logs.size(), 1);
    EXPECT_EQ(logs[0]->level, LogLevel::DEBUG);
    EXPECT_EQ(logs[0]->message, MESSAGE);
}

TEST(LoggerTest, CanPrintLogs) {
    const auto logger = std::make_unique<StringLogger>();

    logger->log(ERROR, "Error message");
    logger->log(WARNING, "Warning message");
    logger->log(INFO, "Info message");
    logger->log(DEBUG, "Debug message");

    auto str = logger->dump();

    std::vector<std::string> logs;
    std::string tmp;
    std::stringstream ss(str);
    while (std::getline(ss, tmp, '\n')) {
        logs.push_back(tmp);
        tmp.clear();
    }
    EXPECT_EQ(std::regex_match(logs[0], errorPattern), true);
    EXPECT_EQ(std::regex_match(logs[1], warningPattern), true);
    EXPECT_EQ(std::regex_match(logs[2], infoPattern), true);
    EXPECT_EQ(std::regex_match(logs[3], debugPattern), true);
}

TEST(LoggerTest, CanPrintAndFlushLogs) {
    const auto logger = std::make_unique<StringLogger>();

    logger->log(ERROR, "Error message");
    logger->log(WARNING, "Warning message");
    logger->log(INFO, "Info message");
    logger->log(DEBUG, "Debug message");

    auto str = logger->dump(true);

    std::string tmp;
    std::vector<std::string> logs;
    std::stringstream ss(str);
    while (std::getline(ss, tmp, '\n')) {
        logs.push_back(tmp);
        tmp.clear();
    }
    EXPECT_EQ(std::regex_match(logs[0], errorPattern), true);
    EXPECT_EQ(std::regex_match(logs[1], warningPattern), true);
    EXPECT_EQ(std::regex_match(logs[2], infoPattern), true);
    EXPECT_EQ(std::regex_match(logs[3], debugPattern), true);

    const auto result = logger->dump();
    EXPECT_EQ(result.empty(), true);
}