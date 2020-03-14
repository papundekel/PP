#pragma once
#include "copy_constructible.hpp"
#include "implicitly_convertible.hpp"

namespace ddecrementable
{
    template <typename T>
    concept x = requires(T t)
    {
        { --t } -> T&;
    };
    template <typename T>
    concept y = requires(T t)
    {
        requires implicitly_convertible_to<decltype(t--), T>;
    };
}
template <typename T>
constexpr auto decrementable_prefix = ddecrementable::x<T>;
template <typename T>
constexpr auto decrementable_postfix = ddecrementable::y<T>;

template <typename T>
constexpr auto decrementable = decrementable_prefix<T> && decrementable_postfix<T>;

template <typename T>
requires decrementable_prefix<T> && copy_constructible<T>
constexpr T operator--(T& t, int)
{
    auto copy = t;
    --t;
    return copy;
}