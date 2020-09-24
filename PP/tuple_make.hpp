#pragma once
#include <tuple>
#include "functional/apply_partially.hpp"
#include "tuple_apply.hpp"

namespace PP
{
	constexpr inline auto tuple_make = apply_partially<false>(tuple_apply,
		[]<typename... T>(T&&... t)
		{
			return std::make_tuple(std::forward<T>(t)...);
		});

	template <typename Tuple>
	constexpr auto tuple_make_default()
	{
		return decltype(tuple_make(std::declval<Tuple>())){};
	}
}
