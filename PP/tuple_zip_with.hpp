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
#include "tuple_map_default.hpp"
#include "tuple_prepend.hpp"
#include "tuple_size.hpp"
#include "tuple_split.hpp"

namespace PP
{
	constexpr inline auto tuple_nonempty = !equal(partial_tag, 0) | tuple_size;

	constexpr inline auto tuple_zip =
	[](tuple_like auto&& tuples)
	{
		if constexpr (tuple_all(tuple_nonempty,
			tuple_map_default<decltype(tuples)>(tuple_make | tuple_map(partial_tag, constant<>(std::tuple<>{}))))
		{
			auto splits = tuple_map(tuple_split, PP_FORWARD(tuples));

			auto heads = tuple_map(tuple_get<0>, std::move(splits));
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
