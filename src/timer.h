#pragma once
#include <chrono>
#include <ctime>
#include <string>


class ATimer {
public:
    virtual std::string getSec() = 0;
    virtual std::string getMin() = 0;
    virtual std::string getHour() = 0;
    virtual std::string getMs() = 0;
    virtual ~ATimer() = default;
};


class Timer : public ATimer {
private:
    using system_clock_t = std::chrono::time_point<std::chrono::system_clock>;

    system_clock_t now_;
    std::time_t now_time_;
    std::tm local_time_;

    system_clock_t now();
    void initTime();

public:
    std::string getSec() override;
    std::string getMin() override;
    std::string getHour() override;
    std::string getMs() override;
};
