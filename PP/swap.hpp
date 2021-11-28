#pragma once
#include <PP/utility/move.hpp>

namespace PP
{
constexpr void swap(auto& a, auto& b)
{
    auto temp = move(a);
    a = move(b);
    b = move(temp);
}
}
