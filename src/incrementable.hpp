#pragma once
#include "value_t.hpp"

namespace concepts
{
    template <typename T>
    concept incrementable = requires(T t)
    {
        { ++t } -> T&;
        { t++ } -> T;
    };
}
template <typename T>
struct incrementable : value_t<concepts::incrementable<T>> {};

template <typename T>
constexpr T operator++(T& t, int)
{
    auto copy = t;
    ++t;
    return copy;
}