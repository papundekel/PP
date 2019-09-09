#pragma once
#include "same.hpp"

namespace dequatable
{
    template <typename T, typename U>
    concept x = requires (T t, U u)
    {
        { t == u } -> bool;
        { u == t } -> bool;
        { t != u } -> bool;
        { u != t } -> bool;
    };
}
template <typename T, typename U = T>
using equatable = val<dequatable::x<T, U>>;

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