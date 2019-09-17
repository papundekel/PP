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
constexpr auto number(T t) { return dnumber::x<untype<T>> && constructible<untype<T>, int> && ordered(t) && assignable(t) && equatable(t) && incrementable(t) && decrementable(t); }

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