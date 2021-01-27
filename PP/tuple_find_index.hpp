#pragma once
#include "size_t.hpp"
#include "tuple_fold.hpp"
#include "utility/move.hpp"

namespace PP
{
	namespace detail
	{
		struct tuple_find_index_state
		{
			size_t index;
			bool found;
		};
	}

	PP_FUNCTOR(tuple_find_index, auto&& predicate, concepts::tuple auto&& tuple)
	{
		return tuple_foldl(
			[&predicate]
			(auto state, auto&& element) -> detail::tuple_find_index_state
			{
				if (state.found || PP_FORWARD(predicate)(PP_FORWARD(element)))
					return { state.index, true };

				return { state.index + 1, false };
			},
			detail::tuple_find_index_state{ 0, false },
			PP_FORWARD(tuple)).index;
	}};
}
