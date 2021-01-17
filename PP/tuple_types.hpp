#pragma once
#include "functional/functor.hpp"
#include "get_type.hpp"
#include "tuple_map.hpp"
#include "type_tuple.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_types, type_wrap auto t)
	{
		return tuple_map();
	}};
}
