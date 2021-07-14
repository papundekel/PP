#pragma once
#include "size_t.hpp"
#include "tuple_find_index_state.hpp"
#include "tuple_fold.hpp"
#include "utility/move.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_find_dynamic,
			   auto&& predicate,
			   concepts::tuple auto&& tuple)
	{
		return tuple_foldl(
				   [predicate_wrap = PP_FORWARD_WRAP(predicate)](
					   detail::tuple_find_index_state state,
					   auto&& element) -> detail::tuple_find_index_state
				   {
					   if (state.found || predicate_wrap--(PP_FORWARD(element)))
						   return {state.index, true};
					   else
						   return {state.index + 1, false};
				   },
				   detail::tuple_find_index_state{0, false},
				   PP_FORWARD(tuple))
			.index;
	});
}
