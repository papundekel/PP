#pragma once
#include "tuple_apply.hpp"
#include "apply_partially.hpp"

namespace PP
{
	constexpr inline auto disjunction = apply_partially<false>(tuple_apply,
		[](auto&&... functions) constexpr
		{
			return
				[...functions = std::forward<decltype(functions)>(functions)](auto&&... args) constexpr
				{
					return (functions(std::forward<decltype(args)>(args)...) || ...);
				};
		});
}
