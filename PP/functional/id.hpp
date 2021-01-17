#pragma once
#include "functor.hpp"
#include "../get_type.hpp"

namespace PP
{
	PP_FUNCTOR(id_typed, type_wrap auto t, PP_GET_TYPE(t) x) -> decltype(auto)
	{
		return static_cast<PP_GET_TYPE(t)>(x);
	}};

	PP_FUNCTOR(id_forward, auto&& x) -> decltype(auto)
	{
		return PP_FORWARD(x);
	}};

	PP_FUNCTOR(id_copy, auto&& x)
	{
		return x;
	}};
}
