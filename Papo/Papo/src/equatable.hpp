#pragma once
template <typename T>
concept equatable = requires(T x, T y)
{
    { x == y } -> bool;
    { y == x } -> bool;
    { x != y } -> bool;
    { y != x } -> bool;
};

template <typename T, typename U>
concept equatable_with = requires(T t, U u)
{
    { t == u } -> bool;
    { u == t } -> bool;
    { t != u } -> bool;
    { u != t } -> bool;
};

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