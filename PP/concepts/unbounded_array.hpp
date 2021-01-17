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

	namespace concepts
	{
		template <typename T>
		concept unbounded_array = is_unbounded_array(type_v<T>);
	}
}
