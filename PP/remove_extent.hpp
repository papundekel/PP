#pragma once
#include "functional/compose.hpp"
#include "get_type.hpp"
#include "overloaded.hpp"
#include "type_t.hpp"

namespace PP
{
	constexpr inline auto remove_extent = functor{ overloaded
	{
		[] <typename T, std::size_t N>(type_t<T[N]>) { return type<T>; },
		[]<typename T>(type_t<T[]>) { return type<T>; },
		[](auto t) { return t; }
	}} | to_type_t;
}
