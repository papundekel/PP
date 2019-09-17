#include "logger.hpp"
#include "output.hpp"

logger::logger()
{
    print("def ctor");
}
logger::logger(const logger&)
{
    print("copy ctor");
}
logger::logger(logger&&) noexcept
{
    print("move ctor");
}
logger& logger::operator=(const logger&)
{
    print("copy assignment");
    return *this;
}
logger& logger::operator=(logger&&)
{
    print("move assignment");
    return *this;
}
logger::~logger()
{
    //print("dtor");
}