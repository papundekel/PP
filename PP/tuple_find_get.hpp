#pragma once
#include "tuple_find.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_find_get, auto&& predicate, concepts::tuple auto&& tuple)
		-> decltype(auto)
	{
		return PP_F(tuple)[tuple_find(PP_F(predicate), PP_F(tuple))];
	});
}
