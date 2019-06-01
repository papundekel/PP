#pragma once
#include "move_.hpp"
template <typename From, typename To>
concept movable_to = requires (From from)
{
    To(move(from));
};
template <typename T>
concept movable = movable_to<T, T>;