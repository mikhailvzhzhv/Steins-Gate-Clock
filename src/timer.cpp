#include "timer.h"


Timer::system_clock_t Timer::now() {
    return std::chrono::system_clock::now();
}

void Timer::initTime() {
    now_ = now();
    now_time_ = std::chrono::system_clock::to_time_t(now_);
    local_time_ = *std::localtime(&now_time_);
}

std::string Timer::getSec() {
    initTime();
    return local_time_.tm_sec < 10 ? "0" + std::to_string(local_time_.tm_sec) : std::to_string(local_time_.tm_sec);
}

std::string Timer::getMin() {
    initTime();
    return local_time_.tm_min < 10 ? "0" + std::to_string(local_time_.tm_min) : std::to_string(local_time_.tm_min);
}

std::string Timer::getHour() {
    initTime();
    return local_time_.tm_hour < 10 ? "0" + std::to_string(local_time_.tm_hour) : std::to_string(local_time_.tm_hour);
}

std::string Timer::getMs() {
    initTime();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now_.time_since_epoch()) % 1000;
    std::string millis = std::to_string(milliseconds.count());
    return std::string(3 - millis.size(), '0') + millis; 
}