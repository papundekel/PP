#pragma once
#include "empty.hpp"
#include "forward_wrap.hpp"
#include "tuple_fold.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_for_each,
			   concepts::value auto left,
			   auto&& f,
			   concepts::tuple auto&& t)
	{
		tuple_fold(
			left,
			[f_wrap = PP_FORWARD_WRAP(f)](empty, auto&& element)
			{
				f_wrap--(PP_FORWARD(element));
				return empty{};
			},
			empty{},
			PP_FORWARD(t));
	});
}
