#pragma once
#include "val.hpp"
#include "val_operators.hpp"

namespace dsame
{
    template <typename T, typename U>
    constexpr auto x = false;
    template <typename T>
    constexpr auto x<T, T> = true;
    
    template <typename T, typename... U>
    using y = AND<val<x<T, U>>...>;
}

template <typename T, typename... U>
struct same : dsame::y<T, U...>
{
    template <typename V>
    using as = dsame::y<T, U..., V>;
};