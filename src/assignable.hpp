#pragma once
#include "forward.hpp"
#include "value_t.hpp"

namespace dassignable_to
{
    template <typename From, typename To>
    concept x = requires (From from, To to)
    {
        { to = frwd<From>(from) } -> To&;
    };
}
template <typename From, typename To = From>
using assignable_to = value_t<dassignable_to::x<From, To>>;

template <typename T>
using assignable = assignable_to<T, T>;