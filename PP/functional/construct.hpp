#pragma once
#include "functor.hpp"
#include "../get_type.hpp"

namespace PP
{
	PP_FUNCTOR(construct, auto t, auto&&... args)
	{
		return PP_GET_TYPE(t)(PP_FORWARD(args)...);
	}};
}
