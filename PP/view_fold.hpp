#pragma once
#include "apply_partially_first.hpp"
#include "functor.hpp"
#include "get_value.hpp"
#include "utility/move.hpp"
#include "view.hpp"

namespace PP
{
	PP_FUNCTOR(view_fold,
	           concepts::value auto left,
	           auto&& f,
	           auto init,
	           concepts::view auto&& v)
	{
		if constexpr (PP_GET_VALUE(left))
		{
			auto i = view_begin(PP_F(v));

			for (; i != view_end(PP_F(v)); ++i)
				init = PP_F(f)(move(init), *i);

			return make_tuple(move(i), move(init));
		}
		else
		{
			auto [begin, i] = view_begin_end(PP_F(v));

			if (begin != i)
			{
				do
				{
					--i;
					init = PP_F(f)(*i, move(init));
				} while (i != begin);
			}

			return make_tuple(move(i), move(init));
		}
	});

	constexpr inline auto view_foldl = view_fold * value_true;
	constexpr inline auto view_foldr = view_fold * value_false;
}