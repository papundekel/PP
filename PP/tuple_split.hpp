#pragma once
#include "functional/applier.hpp"
#include "functional/apply_partially_simple.hpp"
#include "functional/compose.hpp"
#include "overloaded.hpp"
#include "tuple.hpp"
#include "tuple_apply.hpp"
#include "tuple_get.hpp"
#include "tuple_std.hpp"

namespace PP
{
	constexpr inline auto tuple_splitter = make_overloaded_pack
	(
		[](auto&& head, auto&&... tail)
		{
			return tuple<decltype(head), tuple<decltype(tail)...>>
				(placeholder, PP_FORWARD(head), forward_as_tuple(PP_FORWARD(tail)...));
		},
		[]() { return make_tuple(0, 0); }
	);
	
	constexpr inline auto tuple_split = *tuple_splitter;

	constexpr inline auto tuple_head = tuple_get * value_0;
	constexpr inline auto tuple_tail = tuple_get * value_1 | tuple_split;
}
