#pragma once
#include "functional/functor.hpp"
#include "tuple_like.hpp"
#include "value_t.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_get, auto i, tuple_like auto&& tuple) -> decltype(auto)
	{
		return get(i, PP_FORWARD(tuple));
	}};
}
