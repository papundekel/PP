#pragma once
#include "../get_type.hpp"
#include "functor.hpp"

namespace PP
{
	PP_FUNCTOR(id_typed, concepts::type auto t, PP_GET_TYPE(t) x) -> decltype(auto)
	{
		return static_cast<PP_GET_TYPE(t)>(x);
	});

	PP_FUNCTOR(id_forward, auto&& x) -> decltype(auto)
	{
		return PP_FORWARD(x);
	});

	PP_FUNCTOR(id_copy, auto&& x)
	{
		return x;
	});
}
