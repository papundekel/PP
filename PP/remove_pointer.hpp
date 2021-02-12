#pragma once
#include "get_type.hpp"
#include "overloaded.hpp"
#include "type_t.hpp"

namespace PP
{
	constexpr inline auto remove_pointer = functor{ overloaded
	{
		[]<typename T>(type_t<T*>) { return type<T>; },
		[](auto t) { return t; }
	} } | to_type_t;
}
