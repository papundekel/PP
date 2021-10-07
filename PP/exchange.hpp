#pragma once
#include "utility/forward.hpp"
#include "utility/move.hpp"

namespace PP
{
constexpr auto exchange(auto& x, auto&& new_value)
{
    auto old = move(x);
    x = PP_F(new_value);
    return move(old);
}
}
