#pragma once
#include "functional/apply_partially.hpp"
#include "functional/compose.hpp"
#include "overloaded.hpp"
#include "tuple_apply.hpp"
#include "tuple_get.hpp"
#include "tuple_std.hpp"

namespace PP
{
	constexpr inline auto tuple_split = tuple_apply(partial_tag,
		overloaded
		{
			[](auto&& head, auto&&... tail)
			{
				return tuple<decltype(head), tuple<decltype(tail)...>>
					(PP_FORWARD(head), forward_as_tuple(PP_FORWARD(tail)...));
			},
			[]() { return false; }
		});

	constexpr inline auto tuple_head = tuple_get(partial_tag, value_0);
	constexpr inline auto tuple_tail = tuple_get(partial_tag, value_1) | tuple_split;
}
