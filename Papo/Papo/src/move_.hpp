#pragma once
#include "remove_reference.hpp"

template <typename T>
constexpr decltype(auto) move(T&& arg) noexcept
{
	return static_cast<remove_reference<T>&&>(arg);
}