#pragma once
#include "functional/functor.hpp"
#include "forward.hpp"
#include "get_value.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_get, value_wrap auto i, auto&& tuple) -> decltype(auto)
	requires requires { PP_FORWARD(tuple)[i]; }
	{
		return PP_FORWARD(tuple)[i];
	}};
}
