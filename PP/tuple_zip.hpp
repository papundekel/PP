#pragma once
#include <tuple>
#include "tuple_get.hpp"
#include "tuple_split.hpp"
#include "tuple_map.hpp"
#include "tuple_prepend.hpp"
#include "tuple_size.hpp"
#include "tuple_all.hpp"
#include "functional/apply_partially.hpp"
#include "functional/negate.hpp"
#include "functional/equal.hpp"

namespace PP
{
	template <typename Tuples>
	constexpr auto tuple_zip(Tuples) noexcept
	{
		if constexpr (tuple_all(negate | apply_partially(equal, 0) | tuple_size, Tuples{}))
		{
			auto splits = tuple_map(tuple_split, Tuples{});
			return tuple_prepend(map_tuple(tuple_get<0>, splits), tuple_zip(map_tuple(tuple_get<1>, splits)));
		}
		else
			return std::tuple<>{};
	}
}
