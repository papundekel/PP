#pragma once
#include "array.hpp"
#include "functional/applier.hpp"
#include "tuple_like.hpp"

namespace PP
{
	constexpr inline auto tuple_make_array = *make_array;

	constexpr auto operator*(concepts::tuple auto&& t)
	{
		return tuple_make_array(PP_FORWARD(t));
	}
}
