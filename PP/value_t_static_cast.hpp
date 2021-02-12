#pragma once
#include "get_value.hpp"
#include "static_cast.hpp"
#include "value_t.hpp"

namespace PP
{
	PP_FUNCTOR(value_t_static_cast, concepts::type auto t, concepts::value auto v)
	{
		return value<static__cast(t, PP_GET_VALUE(v))>;
	}};
}
