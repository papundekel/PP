#pragma once
#include <PP/utility/forward.hpp>
#include <PP/utility/move.hpp>

namespace PP
{
constexpr auto exchange(auto& x, auto&& new_value)
{
    auto old = move(x);
    x = PP_F(new_value);
    return move(old);
}
}
