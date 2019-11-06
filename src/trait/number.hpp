#pragma once
#include "ordered.hpp"
#include "equatable.hpp"
#include "assignable.hpp"
#include "incrementable.hpp"
#include "decrementable.hpp"
#include "constructible.hpp"

namespace dnumber
{
    template <typename T>
    concept x = requires (T x, const T y)
    {
        { x +  y } -> T;
        { x -  y } -> T;
        { x *  y } -> T;
        { x /  y } -> T;
        { x += y } -> T&;
        { x -= y } -> T&;
        { x *= y } -> T&;
        { x /= y } -> T&;
    };
}
template <typename T>
constexpr auto number = dnumber::x<T> && constructible<T, int> && ordered<T> && assignable<T> && equatable<T> && incrementable<T> && decrementable<T>;

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