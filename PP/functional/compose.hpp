#pragma once
#include "functor.hpp"

namespace PP
{
	PP_FUNCTOR(compose, auto&& f, auto&& g)
	{
		return functor{
			[f = PP_FORWARD(f), g = PP_FORWARD(g)](auto&&... args) -> decltype(auto)
			{
				return f(g(PP_FORWARD(args)...));
			}};
	}};

	constexpr auto operator|(is_functor auto&& f, is_functor auto&& g)
	{
		return compose(PP_FORWARD(f).f, PP_FORWARD(g).f);
	}
}
