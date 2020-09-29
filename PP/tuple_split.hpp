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
	constexpr inline auto tuple_split = apply_partially<false, true>(tuple_apply,
		overloaded{
		[](auto&& head, auto&&... tail)
		{
			return std::pair<decltype(head), std::tuple<decltype(tail)...>>
				(std::forward<decltype(head)>(head), std::forward_as_tuple(std::forward<decltype(tail)>(tail)...));
		},
		[]() { return false; } });

	constexpr inline auto tuple_head = tuple_get<0>;
	constexpr inline auto tuple_tail = tuple_get<1> | tuple_split;
}
