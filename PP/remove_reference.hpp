#pragma once
#include "functional/compose.hpp"
#include "get_type.hpp"
#include "overloaded.hpp"
#include "type_t.hpp"

namespace PP
{
	constexpr inline auto remove_reference = functor{ overloaded
	{
		[]<typename T>(type_t<T  >) { return type_v<T>; },
		[]<typename T>(type_t<T& >) { return type_v<T>; },
		[]<typename T>(type_t<T&&>) { return type_v<T>; }
	}} | to_type_t;

	constexpr auto operator!(type_wrap auto t) noexcept
	{
		return remove_reference(t);
	}
}
