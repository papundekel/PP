#pragma once
#include "remove_type.hpp"
#include "make_volatile.hpp"
template <typename T>
constexpr auto remove_volatile(type<T> t)
{
    return t;
}

template <typename T>
constexpr auto remove_volatile(type<volatile T> t)
{
    return type<T>{};
}