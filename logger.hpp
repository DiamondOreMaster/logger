#pragma once

#include <string>
#include <iostream>
#include <chrono>
#include <format>

const std::string ANSI_RESET = "\033[0m";
const std::string ANSI_RED = "\033[31m";
const std::string ANSI_GREEN = "\033[32m";
const std::string ANSI_YELLOW = "\033[33m";

#ifdef INTERNATIONAL_DATE
std::string GetDateAndTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

    struct tm time_info;
    if (localtime_s(&time_info, &now_time_t)) {
        // Handle the error
        return "";
    }

    int day = time_info.tm_mday;
    int month = time_info.tm_mon + 1;
    int year = time_info.tm_year + 1900;

    int hour = time_info.tm_hour > 12 ? time_info.tm_hour - 12 : time_info.tm_hour;
    int minutes = time_info.tm_min;
    int seconds = time_info.tm_sec;

    return std::format("{}/{}/{} {}:{}:{}", day, month, year, hour, minutes, seconds);
}
#else
std::string GetDateAndTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

    struct tm time_info;
    if (localtime_s(&time_info, &now_time_t)) {
        // Handle the error
        return "";
    }

    int day = time_info.tm_mday;
    int month = time_info.tm_mon + 1;
    int year = time_info.tm_year + 1900;

    int hour = time_info.tm_hour > 12 ? time_info.tm_hour - 12 : time_info.tm_hour;
    int minutes = time_info.tm_min;
    int seconds = time_info.tm_sec;

    return std::format("{}/{}/{} {}:{}:{}", month, day, year, hour, minutes, seconds);
}
#endif // !INTERNATIONAL_DATE

enum class LogType : uint8_t {
    UNKOWN = 0,
    ERROR = 1,
    WARN = 2,
    SUCCESS = 3,
    LOG = 4
};


namespace logger {
    template <typename... Args>
    void print(Args... args) {
        (std::cout << ... << args) << "\n";
    }

    template <typename... Args>
    void log(const std::string& color, LogType logType, Args... rest) {
    #ifdef LOG_TIME
        std::cout << color << "[" << GetDateAndTime() << "] ";
    #else
        std::cout << color;
    #endif // !LOG_TIME

        switch (logType) {
        case LogType::UNKOWN:
            break;
        case LogType::ERROR:
            std::cout << "[ERROR] ";
            break;
        case LogType::WARN:
            std::cout << "[WARNING] ";
            break;
        case LogType::SUCCESS:
            std::cout << "[SUCCESS] ";
            break;
        case LogType::LOG:
            std::cout << "[LOG] ";
            break;
        }
        
        print(rest...);
        std::cout << ANSI_RESET;
    }

    template<typename... Args>
    void ERROR(Args... rest) {
        log(ANSI_RED, LogType::ERROR, rest...);
    }

    template<typename... Args>
    void WARN(Args... rest) {
        log(ANSI_YELLOW, LogType::WARN, rest...);
    }

    template<typename... Args>
    void SUCCESS(Args... rest) {
        log(ANSI_GREEN, LogType::SUCCESS, rest...);
    }

    template<typename... Args>
    void LOG(Args... rest) {
        log(ANSI_RESET, LogType::LOG, rest...);
    }
}