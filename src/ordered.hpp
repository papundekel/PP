#pragma once

template <typename T, typename U>
concept ordered_with_c = requires(T t, U u)
{
    { t < u } -> bool;
    { u < t } -> bool;
    { t > u } -> bool;
    { u > t } -> bool;
};
template <typename T>
concept ordered_c = ordered_with_c<T, T>;

template <typename T, typename U>
constexpr bool operator>(const T& t, const U& u)
{
    return u < t;
}