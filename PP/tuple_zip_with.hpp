#pragma once
#include <tuple>

#include "functional/apply_partially.hpp"
#include "functional/comparisons.hpp"
#include "functional/constant.hpp"
#include "functional/map_arguments.hpp"
#include "functional/negate.hpp"
#include "tuple_all.hpp"
#include "tuple_apply.hpp"
#include "tuple_get.hpp"
#include "tuple_make.hpp"
#include "tuple_map.hpp"
#include "tuple_prepend.hpp"
#include "tuple_size.hpp"
#include "tuple_split.hpp"
#include "tuple_types.hpp"

namespace PP
{
	constexpr inline auto tuple_zip =
	[](tuple_like auto&& tuples)
	{
		if constexpr (tuple_all(!equal(partial_tag, 0) | tuple_type_size, tuple_types(PP_DECLTYPE(tuples))))
		{
			auto splits = tuple_map(tuple_split, PP_FORWARD(tuples));

			auto heads = tuple_map(tuple_get(pari, std::move(splits));
			auto tails = tuple_map(tuple_get<1>, std::move(splits));

			auto zipped_tail = tuple_zip(std::move(tails));

			return tuple_make(
				tuple_prepend(std::move(heads), std::move(zipped_tail)));
		}
		else
			return std::tuple<>{};
	};

	constexpr inline auto tuple_zip_with = [](auto&& f, auto&& tuples) {
		return tuple_map(tuple_apply(partial_tag, PP_FORWARD(f)),
						 tuple_zip(PP_FORWARD(tuples)));
	};
}
