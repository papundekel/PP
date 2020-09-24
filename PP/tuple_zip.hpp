#pragma once
#include <tuple>
#include "tuple_get.hpp"
#include "tuple_split.hpp"
#include "tuple_map.hpp"
#include "tuple_prepend.hpp"
#include "tuple_size.hpp"
#include "tuple_all.hpp"
#include "tuple_make.hpp"
#include "functional/apply_partially.hpp"
#include "functional/negate.hpp"
#include "functional/equal.hpp"

namespace PP
{
	template <typename Tuples>
	constexpr auto tuple_zip(Tuples&& tuples) noexcept
	{
		if constexpr (tuple_all(compose<false>(negate, apply_partially<false>(equal, 0)) || tuple_size, tuple_make_default<Tuples>()))
		{
			auto splits = tuple_make(tuple_map<false>(tuple_split)(std::forward<Tuples>(tuples)));
			
			return tuple_prepend<>(tuple_map<false>(tuple_get<0>)(splits), tuple_zip(tuple_make(tuple_map<false>(tuple_get<1>)(splits))));
		}
		else
			return std::tuple<>{};
	}
}
