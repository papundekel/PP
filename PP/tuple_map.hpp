#pragma once
#include <tuple>
#include <type_traits>
#include "tuple_apply.hpp"
#include "functional/map_arguments.hpp"
#include "functional/id.hpp"

namespace PP
{
	constexpr inline auto tuple_map = map_arguments<false>(tuple_apply,
		[](auto&& map)
		{
			return [&map](auto&&... elements) -> decltype(auto)
			{
				return std::tuple<decltype(std::declval<decltype(map)>()(std::declval<decltype(elements)>()))...>
					(std::forward<decltype(map)>(map)(std::forward<decltype(elements)>(elements))...);
			};
		}
		, id_weak);
}
