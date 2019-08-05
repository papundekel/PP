#pragma once
#include "ordered.hpp"
#include "equatable.hpp"
#include "assignable.hpp"
#include "incrementable.hpp"
#include "decrementable.hpp"

template <typename T>
concept number_c = requires (T x, const T y)
{
    { x +  y } -> T;
    { x -  y } -> T;
    { x *  y } -> T;
    { x /  y } -> T;
    { x += y } -> T&;
	{ x -= y } -> T&;
    { x *= y } -> T&;
    { x /= y } -> T&;
} && ordered_c<T> && assignable_c<T> && equatable_c<T> && incrementable_c<T> && decrementable_c<T>;

template <typename N>
constexpr N& operator+=(N& x, const N& y)
{
    return x = x + y;
}
template <typename N>
constexpr N& operator-=(N& x, const N& y)
{
    return x = x - y;
}
template <typename N>
constexpr N& operator*=(N& x, const N& y)
{
    return x = x * y;
}
template <typename N>
constexpr N& operator/=(N& x, const N& y)
{
    return x = x / y;
}