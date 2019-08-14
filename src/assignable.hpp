#pragma once
#include "forward.hpp"
#include "value_t.hpp"

namespace detail::assignable_to
{
    template <typename From, typename To>
    concept x = requires (From from, To to)
    {
        { to = frwd<From>(from) } -> To&;
    };
}
template <typename From, typename To = From>
struct assignable_to : value_t<detail::assignable_to::x<From, To>> {};

template <typename T>
struct assignable : assignable_to<T, T> {};