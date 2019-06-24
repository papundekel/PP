#pragma once
template <typename T, typename U>
concept equatable_with = requires(T t, U u)
{
    { t == u } -> bool;
    { u == t } -> bool;
    { t != u } -> bool;
    { u != t } -> bool;
};

template <typename T>
concept equatable = equatable_with<T, T>;

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