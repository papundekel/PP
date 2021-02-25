#pragma once
#include "functor.hpp"

namespace PP
{
	PP_FUNCTOR(curry, auto&& f)
	{
		return functor([ff = unwrap_functor(PP_FORWARD(f))]
			(auto&& arg)
			{
				return functor([fff = ff, arg = PP_FORWARD(arg)]
					(auto&&... args) -> decltype(auto)
					{
						return fff(arg, PP_FORWARD(args)...);
					});
			});
	});

	constexpr auto operator~(concepts::functor auto&& f)
	{
		return curry(unwrap_functor(PP_FORWARD(f)));
	}
}
