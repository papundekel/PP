#pragma once
#include "functional/functor.hpp"
#include "get_value.hpp"
#include "utility/forward.hpp"
#include "type_t.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_get, concepts::value auto i, auto&& tuple) -> decltype(auto)
	requires requires { PP_FORWARD(tuple)[i]; }
	{
		return PP_FORWARD(tuple)[i];
	}};
}
