#pragma once

#include <string>
#include <iostream>
#include <chrono>
#include <format>
#include <map>

const std::string ANSI_RESET = "\033[0m";
const std::string ANSI_RED = "\033[31m";
const std::string ANSI_GREEN = "\033[32m";
const std::string ANSI_YELLOW = "\033[33m";

namespace loggerUtils {
    static std::string_view GetDateAndTime() {
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

        std::string date = "";

        #ifdef INTERNATIONAL_DATE
            date = std::format("{}/{}/{} {}:{}:{}", day, month, year, hour, minutes, seconds);
        #else
            date = std::format("{}/{}/{} {}:{}:{}", month, day, year, hour, minutes, seconds);
        #endif

        return date;
    }

    enum class LogType : uint8_t {
        UNKNOWN = 0,
        ERROR = 1,
        WARN = 2,
        SUCCESS = 3,
        LOG = 4
    };

    static std::map<LogType, std::string_view> logTypeStrings = {
        {LogType::UNKNOWN, ""},
        {LogType::ERROR, "[ERROR] "},
        {LogType::WARN, "[WARNING] "},
        {LogType::SUCCESS, "[SUCCESS] "},
        {LogType::LOG, "[LOG] "}
    };
}

namespace logger {
    template <typename... Args>
    static void print(Args... args) {
        (std::cout << ... << args) << "\n";
    }

    template <typename... Args>
    static void log(std::string_view color, loggerUtils::LogType logType, Args... rest) {
        #ifdef LOG_TIME
            std::cout << color << "[" << loggerUtils::GetDateAndTime() << "] ";
        #else
            std::cout << color;
        #endif // !LOG_TIME
        
        std::cout << loggerUtils::logTypeStrings[logType];
        print(rest...);
        std::cout << ANSI_RESET;
    }

    template<typename... Args>
    void ERROR(Args... rest) {
        log(ANSI_RED, loggerUtils::LogType::ERROR, rest...);
        #ifdef EXIT_ON_ERROR
            exit(-1);
        #endif
    }

    template<typename... Args>
    void WARN(Args... rest) {
        log(ANSI_YELLOW, loggerUtils::LogType::WARN, rest...);
    }

    template<typename... Args>
    void SUCCESS(Args... rest) {
        log(ANSI_GREEN, loggerUtils::LogType::SUCCESS, rest...);
    }

    template<typename... Args>
    void LOG(Args... rest) {
        log(ANSI_RESET, loggerUtils::LogType::LOG, rest...);
    }
}