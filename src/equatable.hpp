#pragma once
#include "same.hpp"
#include "not.hpp"

template <typename T, typename U>
concept equatable_with_c = requires(T t, U u)
{
    { t == u } -> bool;
    { u == t } -> bool;
    { t != u } -> bool;
    { u != t } -> bool;
};

template <typename T>
concept equatable_c = equatable_with_c<T, T>;

template <typename T, typename U>
requires !same_c<T, U>
constexpr bool operator==(const T& t, const U& u)
{
    return u == t;
}
template <typename T, typename U>
constexpr bool operator!=(const T& t, const U& u)
{
    return !(t == u);
}