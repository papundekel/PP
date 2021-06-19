#pragma once
#include "empty_tuple.hpp"
#include "forward_wrap.hpp"
#include "functional/apply_partially_first.hpp"
#include "functional/operators.hpp"
#include "tuple_all.hpp"
#include "tuple_apply.hpp"
#include "tuple_count.hpp"
#include "tuple_get.hpp"
#include "tuple_like.hpp"
#include "tuple_make.hpp"
#include "tuple_map.hpp"
#include "tuple_prepend.hpp"
#include "tuple_split.hpp"
#include "tuple_types.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_zip, concepts::tuple auto&& tuples)
	{
		if constexpr (tuple_all(neq * 0_z | tuple_type_count,
								tuple_types(PP_DECLTYPE(tuples))))
		{
			auto splits = tuple_split + PP_FORWARD(tuples);

			return (tuple_make | tuple_prepend)(
				tuple_get * value_0 + move(splits),
				tuple_zip(tuple_get * value_1 + move(splits)));
		}
		else
			return empty_tuple{};
	});
	constexpr inline auto tuple_zip_pack = tuple_zip | forward_as_tuple;

	PP_FUNCTOR(tuple_zip_with, auto&& f, concepts::tuple auto&& tuples)
	{
		return tuple_apply * forward_wrap(PP_FORWARD(f)) +
			   tuple_zip(PP_FORWARD(tuples));
	});
	PP_FUNCTOR(tuple_zip_with_pack, auto&& f, concepts::tuple auto&&... tuples)
	{
		return tuple_zip_with(PP_FORWARD(f),
							  forward_as_tuple(PP_FORWARD(tuples)...));
	});

	constexpr auto operator^(concepts::tuple auto&& a, concepts::tuple auto&& b)
	{
		return tuple_zip_pack(PP_FORWARD(a), PP_FORWARD(b));
	}
}
