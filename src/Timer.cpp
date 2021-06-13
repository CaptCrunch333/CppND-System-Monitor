#include "Timer.hpp"

void Timer::start() {t_start = std::chrono::system_clock::now();}

float Timer::time() { 
    std::chrono::duration<double> t_now = std::chrono::system_clock::now() - t_start;
    return t_now.count();
}