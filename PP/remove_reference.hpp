#pragma once
#include "functional/compose.hpp"
#include "get_type.hpp"
#include "overloaded.hpp"
#include "type_t.hpp"

namespace PP
{
	constexpr inline auto remove_reference = make_overloaded_pack
	(
		[]<typename T>(type_t<T&&>) { return type<T>; },
		[]<typename T>(type_t<T& >) { return type<T>; },
		[](auto t) { return t; }
	) | to_type_t;

	constexpr auto operator!(concepts::type auto t) noexcept
	{
		return remove_reference(t);
	}
}
