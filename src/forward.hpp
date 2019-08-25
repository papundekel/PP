#pragma once
#include "remove_reference.hpp"
#include "reference.hpp"

template <typename T>
constexpr decltype(auto) forward(remove_reference<T>& arg) noexcept
{
	return static_cast<T&&>(arg);
}

template <typename T>
requires !reference_lvalue<T>::v
constexpr decltype(auto) forward(remove_reference<T>&& arg) noexcept
{
	return static_cast<T&&>(arg);
}

template <typename T>
constexpr decltype(auto) frwd(remove_reference<T>& arg) noexcept
{
    if constexpr (!reference<T>::v)
        return static_cast<T&>(arg);
    else
	    return static_cast<T&&>(arg);
}

template <typename T>
requires !reference_lvalue<T>::v
constexpr decltype(auto) frwd(remove_reference<T>&& arg) noexcept
{
	return static_cast<T&&>(arg);
}