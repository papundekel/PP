#pragma once
#include "functor.hpp"
#include "tuple_count.hpp"
#include "tuple_find_dynamic.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_contains, auto&& predicate, concepts::tuple auto&& t)
	{
		return tuple_find_dynamic(PP_F(predicate), PP_F(t)) !=
		       tuple_count(PP_F(t));
	});
}
