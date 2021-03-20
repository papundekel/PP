#pragma once
#include "functional/apply_partially_simple.hpp"
#include "tuple.hpp"
#include "tuple_apply.hpp"
#include "tuple_like.hpp"

namespace PP
{
	constexpr inline auto tuple_make = tuple_apply * make_tuple;
	constexpr inline auto tuple_forward = tuple_apply * forward_as_tuple;

	constexpr auto operator!(concepts::tuple auto&& t)
	{
		return tuple_make(PP_FORWARD(t));
	}
	constexpr auto operator+(concepts::tuple auto&& t) noexcept
	{
		return tuple_forward(PP_FORWARD(t));
	}
}
