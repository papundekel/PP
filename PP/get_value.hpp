#pragma once
#include "get_value.h"
#include "extract_type.hpp"

template <typename T>
requires (!PP::detail::has_value_f<T> && !PP::detail::has_value<T>&& PP::detail::has_type<T>)
constexpr decltype(auto) PP::get_value() noexcept
{
	return extract_type<T>{};
}
