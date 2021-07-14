#pragma once
#include "apply_partially_first.hpp"
#include "empty_tuple.hpp"
#include "iterate_tuple.hpp"
#include "operators.hpp"
#include "singular_tuple.hpp"
#include "tuple_concat.hpp"
#include "tuple_count.hpp"
#include "tuple_zip_with.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_cartesian_product, concepts::tuple auto&& tuples)
	{
		if constexpr (tuple_type_count(PP_DECLTYPE(tuples)) != 0 &&
					  tuple_all(neq * 0_z | tuple_type_count,
								tuple_types(PP_DECLTYPE(tuples))))
		{
			auto [head_tuples, tail_tuples] = tuple_split(PP_FORWARD(tuples));

			return tuple_concats(tuple_zip_with_pack(
				[](auto&& h, auto&& t)
				{
					return tuple_map(
						[&h](auto&& x)
						{
							return tuple_prepend(PP_FORWARD(h), PP_FORWARD(x));
						},
						PP_FORWARD(t));
				},
				PP_FORWARD(head_tuples),
				make_iterate_tuple(
					tuple_count_value_t(head_tuples),
					tuple_cartesian_product(move(tail_tuples)))));
		}
		else
			return make_singular_tuple(empty_tuple{});
	});

	// constexpr inline auto tuple_cartesian_product_pack =
	//	tuple_cartesian_product | forward_as_tuple;

	PP_FUNCTOR(tuple_cartesian_product_pack, concepts::tuple auto&&... tuples)
	{
		return tuple_cartesian_product(forward_as_tuple(PP_FORWARD(tuples)...));
	});
}
