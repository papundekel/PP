#pragma once
#include "ordered.hpp"
#include "equatable.hpp"
#include "assignable.hpp"
#include "incrementable.hpp"
#include "decrementable.hpp"

template <ordered T>
concept number = requires(T x, T y)
{
    { x +  y } -> T;
    { x -  y } -> T;
    { x *  y } -> T;
    { x /  y } -> T;
    { x += y } -> T&;
	{ x -= y } -> T&;
    { x *= y } -> T&;
    { x /= y } -> T&;
} && assignable<T> && equatable<T> && incrementable<T> && decrementable<T>;

template <number N>
auto& operator+=(N& x, const N& y)
{
    return x = x + y;
}
template <number N>
auto& operator-=(N& x, const N& y)
{
    return x = x - y;
}
template <number N>
auto& operator*=(N& x, const N& y)
{
    return x = x * y;
}
template <number N>
auto& operator/=(N& x, const N& y)
{
    return x = x / y;
}