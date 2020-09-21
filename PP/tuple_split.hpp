#pragma once
#include <tuple>
#include <type_traits>
#include "tuple_get.hpp"
#include "functional/compose.hpp"
#include "functional/apply_partially.hpp"
#include "tuple_apply.hpp"

namespace PP
{
	constexpr inline auto tuple_split = apply_partially(tuple_apply,
		[]<typename H, typename... T>(H&& head, T&&... tail)
		{
			return std::forward_as_tuple(std::forward<H>(head), std::forward_as_tuple(std::forward<T>(tail)...));
		});

	constexpr inline auto tuple_head = tuple_get<0>;
	constexpr inline auto tuple_tail = tuple_get<1> | tuple_split;
}
