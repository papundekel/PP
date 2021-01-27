#pragma once
#include "tuple_find_index.hpp"
#include "tuple_get_dynamic.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_find_dynamic, auto&& predicate, concepts::tuple auto&& tuple)
	{
		return tuple_get_dynamic(tuple_find_index(PP_FORWARD(predicate), PP_FORWARD(tuple)), PP_FORWARD(tuple));
	}};
}
