#pragma once
#include <utility>
#include "tuple_map.hpp"
#include "tuple_make.hpp"

namespace PP
{
	template <typename Tuple>
	constexpr auto tuple_map_default(auto&& f)
	{
		return decltype(tuple_make(tuple_map(std::forward<decltype(f)>(f), std::declval<Tuple>()))){};
	}
}
