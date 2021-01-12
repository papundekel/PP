#pragma once
#include "functor.hpp"

namespace PP
{
	PP_FUNCTOR(apply, auto&&... args)
	{
		return functor{
			[...args = PP_FORWARD(args)](auto&& f)
			{
				return PP_FORWARD(f)(args...);
			}};
	}};
}
