#pragma once
#include "../get_type.hpp"
#include "functor.hpp"

namespace PP
{
	PP_FUNCTOR(construct_pack, concepts::type auto t, auto&&... args) -> decltype(auto)
	{
		return PP_GET_TYPE(t)(PP_FORWARD(args)...);
	}};
}
