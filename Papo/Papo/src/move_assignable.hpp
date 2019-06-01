#pragma once
#include "move_.hpp"
template <typename From, typename To>
concept move_assignable_to = requires (From from, To& to)
{
    { to = move(from) } -> To&;
};
template <typename T>
concept move_assignable = move_assignable_to<T, T>;