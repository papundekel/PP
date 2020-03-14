#pragma once
#include "copy_constructible.hpp"

namespace dincrementable_prefix
{
    template <typename T>
    constexpr auto x = requires(T t)
    {
        { ++t } -> T&;
    };
}
template <typename T>
constexpr auto incrementable_prefix = dincrementable_prefix::x<T>;

namespace dincrementable_postfix
{
    template <typename T>
    constexpr auto x = requires(T t)
    {
        { t++ } -> T;
    };
}
template <typename T>
constexpr auto incrementable_postfix = dincrementable_postfix::x<T>;

template <typename T>
constexpr auto incrementable = incrementable_prefix<T> && incrementable_postfix<T>;

template <typename T>
requires copy_constructible<T> && incrementable_prefix<T>
constexpr T operator++(T& t, int)
{
    auto copy = t;
    ++t;
    return copy;
}