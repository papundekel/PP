#pragma once
#include "same.hpp"

namespace dequatable_with
{
    template <typename T, typename U>
    concept z = requires (T t, U u)
    {
        { t == u } -> bool;
        { u == t } -> bool;
        { t != u } -> bool;
        { u != t } -> bool;
    };
}
template <typename T, typename U>
using equatable_with = value_t<dequatable_with::z<T, U>>;

template <typename T>
using equatable = equatable_with<T, T>;

template <typename T, typename U>
requires !same<T, U>::v
constexpr bool operator==(const T& t, const U& u)
{
    return u == t;
}
template <typename T, typename U>
constexpr bool operator!=(const T& t, const U& u)
{
    return !(t == u);
}