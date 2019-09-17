#pragma once
#include "type.hpp"

/*template <typename F, typename T>
constexpr auto remove_type(F f, type<T> t)
{
    return t;
}

template <typename F, typename T>
constexpr auto remove_type(F f, type<decltype(f(type<T>{}))::typename t> t)
{
    return type<T>{};
}*/