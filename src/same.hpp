#pragma once
#include "type.hpp"

template <typename T, typename U>
constexpr auto same(type<T>, type<U>)
{
	return false;
}
template <typename T>
constexpr auto same(type<T>, type<T>)
{
	return true;
}
template <typename T, typename... U>
constexpr auto same(T t, U... u)
{
    return (same(t, u) && ...);
}