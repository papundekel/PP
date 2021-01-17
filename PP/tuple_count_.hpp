#pragma once
#include "tuple_foldr.hpp"
#include "functional/apply_partially.hpp"
#include "functional/map_arguments.hpp"

namespace PP
{
	constexpr inline auto tuple_count_ = map_arguments<>(
		apply_partially<true, true, 1>(tuple_foldr, 0),
		[](auto&& predicate)
		{
			return
				[&predicate](auto&& x, auto&& y) -> std::size_t
				{
					return PP_FORWARD(x)) ? y + 1 : y;
				};
		});
}
