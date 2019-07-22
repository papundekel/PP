#pragma once
#include "forward.hpp"

template <typename From, typename To>
concept assignable_to = requires (From&& from, To& to)
{
    { to = forward<From>(from) } -> To&;
};
template <typename T>
concept assignable = assignable_to<T&, T>;