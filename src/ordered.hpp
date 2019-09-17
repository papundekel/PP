#pragma once
#include "type.hpp"

namespace dordered
{
    template <typename T, typename U>
    concept x = requires(T t, U u)
    {
        { t < u } -> bool;
        { u < t } -> bool;
        { t > u } -> bool;
        { u > t } -> bool;
    };
}
template <typename T, typename U>
constexpr auto ordered(T, U) { return dordered::x<untype<T>, untype<U>>;}
template <typename T>
constexpr auto ordered(T t) { return ordered(t, t); }

template <typename T, typename U>
constexpr bool operator>(const T& t, const U& u)
{
    return u < t;
}