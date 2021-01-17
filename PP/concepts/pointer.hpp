#pragma once
#include "../functional/compose.hpp"
#include "../get_type.hpp"
#include "../overloaded.hpp"

namespace PP
{
	constexpr inline auto is_pointer = functor{ overloaded
	{
		[] <typename T>(type_t<T*>) { return true; },
		[](auto t) { return false; }
	}} | to_type_t;

	namespace concepts
	{
		template <typename T>
		concept pointer = is_pointer(type_v<T>);
	}
}
