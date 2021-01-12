#pragma once
#include "functional/functor.hpp"
#include "tuple_find.hpp"
#include "tuple_size.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_contains, auto&& predicate, tuple_like auto&& tuple)
	{
		return tuple_find_index(PP_FORWARD(predicate), PP_FORWARD(tuple))
			!= tuple_size(PP_FORWARD(tuple));
	}};
}
