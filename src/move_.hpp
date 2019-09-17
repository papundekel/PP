#pragma once
#include "remove_reference.hpp"

template <typename T>
constexpr decltype(auto) move(T&& arg) noexcept
{
	return static_cast<decl_type<remove_reference(type<T>{})>&&>(arg);
}