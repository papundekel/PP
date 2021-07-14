#pragma once
#include "functor_or_wrap.hpp"

namespace PP
{
	constexpr auto operator&&(concepts::functor_or_wrap auto&& f,
							  concepts::functor_or_wrap auto&& g)
	{
		return functor(
			[f = unwrap_functor(PP_FORWARD(f)),
			 g = unwrap_functor(PP_FORWARD(g))](
				auto&&... args) -> decltype(auto)
			{
				return unwrap_functor_or_wrap(f)(PP_FORWARD(args)...) &&
					   unwrap_functor_or_wrap(g)(PP_FORWARD(args)...);
			});
	}
}
