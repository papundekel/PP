#pragma once
#include "tuple_foldr.hpp"
#include "functional/apply_partially.hpp"
#include "functional/map_arguments.hpp"

namespace PP
{
	constexpr inline auto tuple_count = map_arguments<>(
		apply_partially<true, true, 1>(tuple_foldr, 0),
		[](auto&& predicate)
		{
			return
				[&predicate](auto&& x, auto&& y) -> std::size_t
				{
					return std::forward<decltype(predicate)>(predicate)(std::forward<decltype(x)>(x)) ? y + 1 : y;
				};
		});
}
