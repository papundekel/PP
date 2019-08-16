#include "logger.hpp"
#include "output.hpp"

bim::bim()
{
    print("def ctor");
}
bim::bim(const bim&)
{
    print("copy ctor");
}
bim::bim(bim&&) noexcept
{
    print("move ctor");
}
bim& bim::operator=(const bim&)
{
    print("copy assignment");
    return *this;
}
bim& bim::operator=(bim&&)
{
    print("move assignment");
    return *this;
}
bim::~bim()
{
    print("dtor");
}