#pragma once
#include "forward.hpp"

template <typename From, typename To = From>
concept assignable_to = requires (From from, To to)
{
    { to = frwd<From>(from) } -> To&;
};
template <typename T>
concept assignable = assignable_to<T>;