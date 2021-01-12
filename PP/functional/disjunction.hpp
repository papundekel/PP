#pragma once
#include "tuple_apply.hpp"
#include "apply_partially.hpp"

namespace PP
{
	constexpr inline auto disjunction = apply_partially(tuple_apply,
		[](auto&&... functions)
		{
			return functor
			{
				[...functions = PP_FORWARD(functions)](auto&&... args) -> decltype(auto)
				{
					return (functions(PP_FORWARD(args)...) || ...);
				}
			};
		});
}
