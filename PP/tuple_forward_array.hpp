#pragma once
#include "forward_wrap.hpp"
#include "functional/apply_partially.hpp"
#include "functional/compose.hpp"
#include "tuple_make_array.hpp"
#include "tuple_map.hpp"

namespace PP
{
	constexpr inline auto tuple_forward_array = tuple_make_array | tuple_map * fwrap;

	constexpr auto operator~(concepts::tuple auto&& t) noexcept
	{
		return tuple_forward_array(PP_FORWARD(t));
	}
}
