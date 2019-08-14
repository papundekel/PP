#pragma once
#include <chrono>

class timer
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start;

public:
    timer();
    ~timer();

    void stop();
};