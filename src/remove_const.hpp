#pragma once
#include "remove_type.hpp"
#include "make_const.hpp"
template <typename T>
constexpr auto remove_const(type<T> t)
{
    return t;
}

template <typename T>
constexpr auto remove_const(type<const T> t)
{
    return type<T>{};
}