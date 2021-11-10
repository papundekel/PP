#pragma once

namespace PPtest
{
struct counter
{
    int& x;

    counter(int& x) noexcept;
    counter(const counter& n) noexcept;
};
}
