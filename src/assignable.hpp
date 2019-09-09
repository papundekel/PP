#pragma once
#include "forward.hpp"
#include "val.hpp"

namespace dassignable
{
    template <typename From, typename To>
    concept x = requires (From from, To to)
    {
        { to = frwd<From>(from) } -> To&;
    };
}
template <typename From, typename To = From>
using assignable = val<dassignable::x<From, To>>;