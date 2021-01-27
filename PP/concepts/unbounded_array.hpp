#pragma once
#include "../functional/compose.hpp"
#include "../get_type.hpp"
#include "../overloaded.hpp"

namespace PP
{
	constexpr inline auto is_unbounded_array = functor{ overloaded
	{
		[] <typename T>(type_t<T[]>) { return true; },
		[](auto t) { return false; }
	}} | to_type_t;

	PP_CONCEPT1(unbounded_array)
}
