#pragma once
#include <type_traits>
#include "tuple.hpp"
#include "pair.hpp"
#include "tuple_get.hpp"
#include "functional/compose.hpp"
#include "functional/apply_partially.hpp"
#include "tuple_apply.hpp"
#include "overloaded.hpp"

namespace PP
{
	namespace detail
	{
		constexpr inline struct tuple_split_fail_t {} tuple_split_fail;
	}

	constexpr inline auto tuple_split = apply_partially<false>(tuple_apply,
		overloaded{
		[](auto&& head, auto&&... tail)
		{
			return std::pair<decltype(head), std::tuple<decltype(tail)...>>
				(PP_FORWARD(head), std::forward_as_tuple(PP_FORWARD(tail)...));
		},
		[]() { return false; } });

	constexpr inline auto tuple_head = tuple_get<0>;
	constexpr inline auto tuple_tail = tuple_get<1> | tuple_split;
}
