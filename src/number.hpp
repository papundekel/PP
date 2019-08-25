#pragma once
#include "ordered.hpp"
#include "equatable.hpp"
#include "assignable.hpp"
#include "incrementable.hpp"
#include "decrementable.hpp"
#include "constructible.hpp"

namespace detail::number
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
using number = value_t<detail::number::x<T> && constructible<T, int>::v && ordered<T>::v && assignable<T>::v && equatable<T>::v && incrementable<T>::v && decrementable<T>::v>;

template <typename N>
//requires requires (N& a, const N& b) { a = a + b; }
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