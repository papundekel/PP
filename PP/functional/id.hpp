#pragma once
#include "functor.hpp"
#include "../type_t.hpp"

namespace PP
{
	PP_FUNCTOR(id, auto t, type_t<PP_GET_TYPE(t)>::type x) -> decltype(auto)
	{
		return static_cast<PP_GET_TYPE(t)>(x);
	}};

	PP_FUNCTOR(id_weak, auto&& x) -> decltype(auto)
	{
		return PP_FORWARD(x);
	}};
}
