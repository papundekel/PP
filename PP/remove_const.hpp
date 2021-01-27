#pragma once
#include "functional/compose.hpp"
#include "get_type.hpp"
#include "overloaded.hpp"
#include "type_t.hpp"

namespace PP
{
	constexpr inline auto remove_const = functor{ overloaded
	{
		[]<typename T>(type_t<const T>) { return type<T>; },
		[](auto t) { return t; }
	}} | to_type_t;
}
