#pragma once
#include <tuple>
#include "functional/apply_partially.hpp"
#include "tuple_apply.hpp"

namespace PP
{
	constexpr inline auto tuple_make = tuple_apply<>(
		[]<typename... T>(T&&... t)
		{
			return std::make_tuple(std::forward<T>(t)...);
		});
}
