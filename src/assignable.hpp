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
template <typename From, typename To>
constexpr auto assignable(From, To) { return dassignable::x<untype<From>, untype<To>>; }

template <typename T>
constexpr auto assignable(T t) { return assignable(t, t); }