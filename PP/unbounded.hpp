#pragma once
#include "iterator.hpp"

namespace PP
{
	constexpr inline struct unbounded_t{} unbounded{};

	constexpr bool operator==(concepts::iterator auto, unbounded_t) noexcept
	{
		return false;
	}
}
