#pragma once
#include "functional/operators.hpp"
#include "tuple.hpp"
#include "tuple_for_each.hpp"
#include "tuple_make.hpp"
#include "tuple_map.hpp"
#include "tuple_zip_with.hpp"
#include "utility/move.hpp"
#include "view.hpp"

namespace PP
{
	PP_FUNCTOR(view_zip_if,
			   auto&&				  predicate,
			   auto&&				  f,
			   concepts::tuple auto&& views)
	{
		auto begin_ends = view_begin_end + PP_FORWARD(views);
		auto is = tuple_get * value_0 + begin_ends;

		while (*neq && begin_ends)
		{
			auto dereferenced = der + is;

			auto [cond, do_step] =
				tuple_apply(PP_FORWARD(predicate), move(dereferenced));

			if (cond)
				tuple_apply(PP_FORWARD(f), move(dereferenced));

			tuple_for_each(value_true,
						   applier(
							   [](bool step, auto& i)
							   {
								   if (step)
									   ++i;
							   }),
						   do_step ^ is);
		}

		return !is;
	});

	PP_FUNCTOR(view_zip_if_pack,
			   auto&& predicate,
			   auto&& f,
			   concepts::view auto&&... views)
	{
		return view_zip_if(PP_FORWARD(predicate),
						   PP_FORWARD(f),
						   forward_as_tuple(PP_FORWARD(views)...));
	});
}
