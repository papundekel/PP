#pragma once
#include "functional/apply_partially.hpp"
#include "tuple_fold.hpp"
#include "tuple_prepend.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_concat, concepts::tuple auto&& l, concepts::tuple auto&& r)
	{
		return tuple_foldr(tuple_prepend, PP_FORWARD(r), PP_FORWARD(l));
	});
}
