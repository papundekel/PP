#pragma once
#include "tuple_fold.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_count_, auto&& predicate, concepts::tuple auto&& t)
	{
		return tuple_foldl([&predicate]
			(auto counter, auto&& element)
			{
				return PP_FORWARD(predicate)(PP_FORWARD(element)) ? counter + 1 : counter;
			}, size_t(0), PP_FORWARD(t));
	});
}
