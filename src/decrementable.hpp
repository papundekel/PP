#pragma once
#include "copy_constructible.hpp"
#include "implicitly_convertible.hpp"

namespace ddecrementable_prefix
{
    template <typename T>
    concept x = requires(T t)
    {
        { --t } -> T&;
    };
}
template <typename T>
using decrementable_prefix = value_t<ddecrementable_prefix::x<T>>;

namespace ddecrementable_postfix
{
    template <typename T>
    concept x = requires(T t)
    {
        requires implicitly_convertible_to<decltype(t--), T>::v;
    };
}
template <typename T>
using decrementable_postfix = value_t<ddecrementable_postfix::x<T>>;

template <typename T>
using decrementable = value_t<decrementable_prefix<T>::v && decrementable_postfix<T>::v>;

template <typename T>
requires decrementable_prefix<T>::v && copy_constructible<T>::v
constexpr T operator--(T& t, int)
{
    auto copy = t;
    --t;
    return copy;
}