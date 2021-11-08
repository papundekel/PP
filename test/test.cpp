#include "test.hpp"

test::counter::counter(int& x) noexcept
    : x(x)
{
    x = 0;
}

test::counter::counter(const counter& n) noexcept
    : x(n.x)
{
    ++x;
}
