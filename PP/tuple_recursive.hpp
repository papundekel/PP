#pragma once
#include "tuple_pred.hpp"
#include "get_value.hpp"
#include "tuple_count.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_recursive, auto&& f, value_wrap auto i, auto&& t) -> decltype(auto)
	requires
		requires { PP_FORWARD(f)(PP_FORWARD(t)); } &&
		(*PP_COPY_VALUE(i) == 0 || requires { tuple_pred(PP_FORWARD(t)); }) &&
		(*PP_COPY_VALUE(i) < tuple_type_count(PP_DECLTYPE(t)))
	{
		if constexpr (*PP_COPY_VALUE(i) == 0)
			return PP_FORWARD(f)(PP_FORWARD(t));
		else
			return tuple_recursive(PP_FORWARD(f), i - value_1, tuple_pred(PP_FORWARD(t)));
	}};
}
