#pragma once
#include "val.hpp"

namespace dincrementable
{
    template <typename T>
    concept x = requires(untype<T> t)
    {
        { ++t } -> untype<T>&;
        { t++ } -> untype<T>;
    };
}
template <typename T>
constexpr auto incrementable(T) { return dincrementable::x<T>; }

template <typename T>
constexpr T operator++(T& t, int)
{
    auto copy = t;
    ++t;
    return copy;
}