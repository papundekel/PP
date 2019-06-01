#pragma once
#include "remove_reference.hpp"
#include "is_reference_lvalue.hpp"

template <typename T>
constexpr T&& forward(remove_reference<T>& arg) noexcept
{
	return static_cast<T&&>(arg);
}

template <typename T>
constexpr T&& forward(remove_reference<T>&& arg) noexcept
{
	static_assert(!is_reference_lvalue<T>, "forward: !is_reference_lvalue<T> failed");
	return static_cast<T&&>(arg);
}