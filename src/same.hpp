#pragma once
#include "value_t.hpp"

namespace detail::same
{
    template <typename T, typename... U>
    constexpr auto x = true;
    template <typename T, typename U, typename ...V>
    constexpr auto x<T, U, V...> = x<T, U> && x<U, V...>;
    template <typename T, typename U>
    constexpr auto x<T, U> = false;
    template <typename T>
    constexpr auto x<T, T> = true;
}

template <typename T, typename... U>
struct same : value_t<detail::same::x<T, U...>>
{
    template <typename V>
    using as = value_t<detail::same::x<T, U..., V>>;
};