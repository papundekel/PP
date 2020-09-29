#pragma once
#include <tuple>
#include "tuple_get.hpp"
#include "tuple_split.hpp"
#include "tuple_map.hpp"
#include "tuple_prepend.hpp"
#include "tuple_size.hpp"
#include "tuple_all.hpp"
#include "tuple_make.hpp"
#include "tuple_map_default.hpp"
#include "functional/apply_partially.hpp"
#include "functional/negate.hpp"
#include "functional/equal.hpp"
#include "functional/constant.hpp"

namespace PP
{
	template <tuple_like Tuples>
	constexpr auto tuple_zip(Tuples&& tuples) noexcept
	{
		if constexpr (tuple_all(compose<false>(negate, apply_partially<false>(equal, std::make_index_sequence<0>{}, 0)) || tuple_size,
			tuple_map_default<Tuples>(compose<false>(tuple_make, apply_partially<false>(tuple_map, std::make_index_sequence<0>{}, constant<>(std::tuple<>{}))))))
		{
			auto splits = tuple_map(tuple_split, std::forward<Tuples>(tuples));
			return tuple_make(tuple_prepend(tuple_map(tuple_get<0>, splits), tuple_zip(tuple_map(tuple_get<1>, splits))));
		}
		else
			return std::tuple<>{};
	}
}
