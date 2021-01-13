#pragma once
#include "functor.hpp"

namespace PP
{
	PP_FUNCTOR(equal, auto&& x, auto&& y) -> decltype(auto)
	{
		return PP_FORWARD(x) == PP_FORWARD(y);
	}};
	PP_FUNCTOR(less_or_eq, auto&& x, auto&& y) -> decltype(auto)
	{
		return PP_FORWARD(x) <= PP_FORWARD(y);
	}};
}
