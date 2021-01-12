#pragma once
#include "iterator.hpp"

namespace PP
{
	struct unbounded_t {};
	inline constexpr unbounded_t unbounded{};

	constexpr bool operator==(concepts::iterator auto, unbounded_t) { return false; }
}
