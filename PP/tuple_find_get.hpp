#pragma once
#include "tuple_find.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_find_get, auto&& predicate, concepts::tuple auto&& tuple) -> decltype(auto)
	{
		return PP_FORWARD(tuple)[tuple_find(PP_FORWARD(predicate), PP_FORWARD(tuple))];
	});
}
