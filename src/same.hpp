#pragma once
#include "value_t.hpp"

namespace dsame
{
    template <typename T, typename U>
    constexpr auto x = false;
    template <typename T>
    constexpr auto x<T, T> = true;

    template <typename T, typename... U>
    using y = value_t<(x<T, U> && ...)>;
}

template <typename T, typename... U>
struct same : dsame::y<T, U...>
{
    template <typename V>
    using as = dsame::y<T, U..., V>;
};