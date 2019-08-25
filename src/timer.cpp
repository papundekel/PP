#include "timer.hpp"
#include "output.hpp"
timer::timer()
    : start(std::chrono::high_resolution_clock::now())
{}

timer::~timer()
{
    stop();
}

void timer::stop()
{
    //print(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count() * 0.001);
}