#pragma once
#include "applier.hpp"
#include "array.hpp"
#include "tuple_concept.hpp"

namespace PP
{
	constexpr inline auto tuple_forward_array = *forward_as_array;

	constexpr auto operator~(concepts::tuple auto&& t)
	{
		return tuple_forward_array(PP_F(t));
	}
}
