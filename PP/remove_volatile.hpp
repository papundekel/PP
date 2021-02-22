#pragma once
#include "functional/compose.hpp"
#include "get_type.hpp"
#include "overloaded.hpp"
#include "type_t.hpp"

namespace PP
{
	constexpr inline auto remove_volatile = make_overloaded_pack
	(
		[]<typename T>(type_t<volatile T>) { return type<T>; },
		[](auto t) { return t; }
	) | to_type_t;
}
