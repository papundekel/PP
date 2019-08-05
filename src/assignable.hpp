#pragma once
#include "forward.hpp"

template <typename From, typename To = From>
concept assignable_to_c = requires (From from, To to)
{
    { to = frwd<From>(from) } -> To&;
};
template <typename T>
concept assignable_c = assignable_to_c<T>;