#pragma once
#include <tuple>
#include "tuple_apply.hpp"
#include "functional/map_arguments.hpp"
#include "functional/id.hpp"

namespace PP
{
	constexpr inline auto tuple_prepend = map_arguments<false>(tuple_apply,
		[](auto&& head)
		{
			return [&head](auto&&... elements)
			{
				return std::tuple<decltype(head), decltype(elements)...>
					(std::forward<decltype(head)>(head), std::forward<decltype(elements)>(elements)...);
			};
		}, id_weak);
}
