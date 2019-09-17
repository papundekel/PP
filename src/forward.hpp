#pragma once
#include "remove_reference.hpp"
#include "reference.hpp"
#include "conditional.hpp"

template <typename T>
constexpr decltype(auto) forward(T& arg) noexcept
{
	return static_cast<T&&>(arg);
}