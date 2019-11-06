#pragma once
#include "type.hpp"

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
constexpr auto equatable = dequatable::x<T, U>;

template <typename T, typename U>
constexpr bool operator==(const T& t, const U& u)
{
    return u == t;
}
template <typename T, typename U>
constexpr bool operator!=(const T& t, const U& u)
{
    return !(t == u);
}