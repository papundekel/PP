#pragma once
#include "equatable.hpp"
#include "ordered.hpp"
#include "incrementable.hpp"
#include "decrementable.hpp"
template <typename T>
concept arithmetic = requires(T x, T y)
{
    { x + y } -> T;
    { x - y } -> T;
    { x * y } -> T;
    { x / y } -> T;
    { -x } -> T;
    { x += y } -> T&;
    { x -= y } -> T&;
    { x *= y } -> T&;
    { x /= y } -> T&;
} && equatable<T> && ordered<T> && incrementable<T> && decrementable<T>;

template <arithmetic A>
auto& operator+=(A& lhs, const A& rhs)
{
    return lhs = lhs + rhs;
}
template <arithmetic A>
auto& operator-=(A& lhs, const A& rhs)
{
    return lhs = lhs - rhs;
}
template <arithmetic A>
auto& operator*=(A& lhs, const A& rhs)
{
    return lhs = lhs * rhs;
}
template <arithmetic A>
auto& operator/=(A& lhs, const A& rhs)
{
    return lhs = lhs / rhs;
}