#pragma once
#include "empty_tuple.hpp"
#include "forward_wrap.hpp"
#include "get_value.hpp"
#include "tuple.hpp"
#include "tuple_fold.hpp"
#include "tuple_make.hpp"
#include "tuple_prepend.hpp"
#include "tuple_zip_indices.hpp"
#include "type_t.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_splits, auto&& predicate, concepts::tuple auto&& t)
	{
		return tuple_foldr(
			[predicate_wrap = PP_FORWARD_WRAP(predicate)](auto&& element,
														  auto	 splits)
			{
				if constexpr (PP_GET_VALUE(
								  predicate_wrap.unwrap()(PP_FORWARD(element))))
					return !tuple_prepend(empty_tuple{}, move(splits));
				else
					return *functor(
							   [element_wrap = PP_FORWARD_WRAP(element)](
								   concepts::value auto i, auto split)
							   {
								   if constexpr (PP_GET_VALUE(i) == 0)
									   return tuple_prepend(
										   element_wrap.unwrap(), move(split));
								   else
									   return move(split);
							   }) +
						   tuple_zip_indices(move(splits));
			},
			make_tuple(empty_tuple{}),
			PP_FORWARD(t));
	});
}
