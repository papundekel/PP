#pragma once
#include "size_t.hpp"
#include "tuple_find_index_state.hpp"
#include "tuple_fold.hpp"
#include "utility/move.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_find, auto&& predicate, concepts::tuple auto&& tuple)
	{
		return PP_COPY_VALUE_MEMBER(tuple_foldl([predicate_wrap = PP_FORWARD_WRAP(predicate)]
			(concepts::value auto s, auto&& element)
			{
				constexpr auto state = PP_GET_VALUE(s);

				if constexpr (state.found || PP_GET_VALUE(predicate_wrap.unwrap()(PP_FORWARD(element))))
					return value<detail::tuple_find_index_state(state.index, true)>;
				else
					return value<detail::tuple_find_index_state(state.index + 1, false)>;
			},
			value<detail::tuple_find_index_state(0, false)>,
			PP_FORWARD(tuple)), index);
	});
}
