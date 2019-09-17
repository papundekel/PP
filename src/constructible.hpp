#pragma once
#include "type.hpp"
#include "declval.hpp"

template <typename T, typename... Args>
constexpr bool constructible = requires
{
    T(declval<Args>()...);
};