#pragma once
#include "../functional/compose.hpp"
#include "../get_type.hpp"
#include "../overloaded.hpp"

namespace PP
{
	constexpr inline auto is_pointer_to_member = functor{ overloaded
	{
		[] <typename T, typename Class>(type_t<T Class::*>) { return true; },
		[](auto t) { return false; }
	} } | to_type_t;

	namespace concepts
	{
		template <typename T>
		concept pointer_to_member = is_pointer_to_member(type_v<T>);
	}
}
