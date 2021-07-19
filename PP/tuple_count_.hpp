#pragma once
#include "constant.hpp"
#include "tuple_fold.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_count_, auto&& predicate, concepts::tuple auto&& t)
	{
		return tuple_foldl(
			[&predicate](auto counter, auto&& element)
			{
				return PP_F(predicate)(PP_F(element)) ? counter + 1 : counter;
			},
			constant(0_z),
			PP_F(t));
	});
}
