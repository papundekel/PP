#pragma once
#include "declval.hpp"

template <typename T, typename ...Args>
concept constructible = requires
{
    T(declval<Args>()...);
};