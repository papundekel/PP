#pragma once
#include "../functional/functor.hpp"
#include "../get_type.hpp"
#include "../macros/simple_concept.hpp"

namespace PP
{
	PP_FUNCTOR(is_union, concepts::type auto t)
	{
		return __is_union(PP_GET_TYPE(t));
	});

	PP_CONCEPT(union_type, union)
}
