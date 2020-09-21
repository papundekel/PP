#pragma once
#include <tuple>
#include "tuple_apply.hpp"
#include "functional/apply_partially.hpp"

namespace PP
{
	constexpr inline auto disjunction = apply_partially(tuple_apply,
		[]<typename... F>(F&&... functions)
		{
			return
				[&functions...]<typename... U>(U&&... x)
				{
					return (std::forward<F>(functions)(std::forward<U>(x)...) || ...);
				};
		});
}
