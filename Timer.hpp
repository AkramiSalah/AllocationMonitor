#pragma once
#include <chrono>
#include <iostream>
#include <string>
#include <string_view>

class Timer {
public:
    explicit Timer() : m_start(std::chrono::steady_clock::now()) {}

    double elapsedMs() const {
        auto now = std::chrono::steady_clock::now();
        return std::chrono::duration<double, std::milli>(now - m_start).count();
    }

    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;
    Timer(Timer&&) = delete;
    Timer& operator=(Timer&&) = delete;

private:
    const std::chrono::time_point<std::chrono::steady_clock> m_start;
};