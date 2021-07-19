#pragma once
#include "apply_partially_first.hpp"
#include "declval.hpp"
#include "forward_wrap.hpp"
#include "functor.hpp"
#include "tuple.hpp"
#include "tuple_apply.hpp"
#include "wrap.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_map, auto&& map, concepts::tuple auto&& t)
	{
		return functor(
			[m = PP_FORWARD_WRAP(map)](auto&&... elements)
			{
				return tuple(in_place,
			                 (cal * m * PP_FORWARD_WRAP(elements))...);
			})[PP_F(t)];
	});

	constexpr auto operator+(concepts::wrap auto&& f,
	                         concepts::tuple auto&& tuple)
	{
		return tuple_map(unwrap(PP_F(f)), PP_F(tuple));
	}
}
