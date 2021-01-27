#pragma once
#include "../functional/compose.hpp"
#include "../get_type.hpp"
#include "../overloaded.hpp"
#include "../remove_cv.hpp"

namespace PP
{
	constexpr inline auto is_pointer = functor{ overloaded
	{
		[] <typename T>(type_t<T*>) { return true; },
		[](auto t) { return false; }
	}} | remove_cv;

	PP_CONCEPT1(pointer)
}
