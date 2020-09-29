#pragma once
#include <tuple>
#include "functional/apply_partially.hpp"
#include "tuple_apply.hpp"

namespace PP
{
	constexpr inline auto tuple_make = apply_partially<false>(tuple_apply,
		[](auto&&... t)
		{
			return std::make_tuple(std::forward<decltype(t)>(t)...);
		});
}
