#pragma once
#include "functor.hpp"

namespace PP
{
	PP_FUNCTOR(constant, auto&& c)
	{
		return functor{
			[c = PP_FORWARD(c)](auto&&...)
			{
				return c;
			}};
	}};
}
