#pragma once
#include "type/remove_ref.hpp"

template <typename T>
constexpr decltype(auto) move(T&& arg) noexcept
{
	return static_cast<get_type<remove_ref(t<T>)>&&>(arg);
}