#pragma once
#include "remove_reference.hpp"
#include "reference_lvalue.hpp"

template <typename T>
constexpr T&& forward(remove_reference<T>& arg) noexcept
{
	return static_cast<T&&>(arg);
}

template <typename T>
requires !reference_lvalue<T>
constexpr T&& forward(remove_reference<T>&& arg) noexcept
{
	return static_cast<T&&>(arg);
}