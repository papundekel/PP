#pragma once
#include "../size_t.hpp"
#include "fold.hpp"

namespace PP::tuple
{
PP_FUNCTOR(count_if, auto&& pp, concepts::tuple auto&& t)
{
	return foldl(
		[p = PP_FW(pp)](auto counter, auto&& element)
		{
			return p(PP_F(element)) ? counter + 1 : counter;
		},
		0_z,
		PP_F(t));
});
}
