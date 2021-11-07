#include "PPtest.hpp"

PPtest::counter::counter(int& x) noexcept
    : x(x)
{
    x = 0;
}

PPtest::counter::counter(const counter& n) noexcept
    : x(n.x)
{
    ++x;
}
