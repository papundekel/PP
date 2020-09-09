#pragma once
#include "get_value.h"

template <typename Value>
struct extract_value
{
	static constexpr decltype(auto) value_f() noexcept
	{
		return get_value<Value>();
	}
};
