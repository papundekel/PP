#include "logger.hpp"
#include "output.hpp"

size_t logger::count = 0;

logger::logger()
    : constructor(logger::def)
    , origin(0)
    , index(count++)
{
    print((std::to_string(index) + std::string(" def")).c_str());
}
logger::logger(const logger& l)
    : constructor(logger::cop)
    , origin(l.index)
    , index(count++)
{
    print((std::to_string(index) + std::string(" copied from ") + std::to_string(origin)).c_str());
}
logger::logger(logger&& l) noexcept
    : constructor(logger::mov)
    , origin(l.index)
    , index(count++)
{
    print((std::to_string(index) + std::string(" moved from ") + std::to_string(origin)).c_str());
}
logger& logger::operator=(const logger& l)
{
    print((std::to_string(index) + std::string(" copy assigned from ") + std::to_string(l.index)).c_str());
    return *this;
}
logger& logger::operator=(logger&& l)
{
    print((std::to_string(index) + std::string(" move assigned from ") + std::to_string(l.index)).c_str());
    return *this;
}
logger::~logger()
{
    --count;
    print((std::to_string(index) +  std::string(" died")).c_str());
}