#pragma once
#include "value_t.hpp"
namespace dordered_with
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
using ordered_with = value_t<dordered_with::x<T, U>>;

template <typename T>
using ordered = ordered_with<T, T>;

template <typename T, typename U>
constexpr bool operator>(const T& t, const U& u)
{
    return u < t;
}