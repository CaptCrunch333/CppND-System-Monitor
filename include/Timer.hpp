#pragma once
#include <ctime>
#include <chrono>

class Timer {
    private:
        std::chrono::time_point<std::chrono::system_clock> t_start;
    public:
        void start();
        float time();
};