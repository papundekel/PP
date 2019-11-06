#pragma once
#include "forward.hpp"
#include "val.hpp"

namespace dassignable
{
    template <typename From, typename To>
    concept x = requires (From from, To to)
    {
        { to = forward<From>(from) } -> To&;
    };
}
template <typename From, typename To = From>
constexpr auto assignable = dassignable::x<From, To>;