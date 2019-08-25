#pragma once
#include "value_t.hpp"

namespace dincrementable
{
    template <typename T>
    concept x = requires(T t)
    {
        { ++t } -> T&;
        { t++ } -> T;
    };
}
template <typename T>
using incrementable = value_t<dincrementable::x<T>>;

template <typename T>
constexpr T operator++(T& t, int)
{
    auto copy = t;
    ++t;
    return copy;
}