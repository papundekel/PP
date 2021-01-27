#pragma once
#include "utility/forward.hpp"

namespace PP
{
	constexpr auto exchange(auto& x, auto&& new_value)
	{
		auto old = std::move(x);
		x = PP_FORWARD(new_value);
		return old;
	}
}
