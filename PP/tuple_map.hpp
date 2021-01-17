#pragma once
#include "tuple.hpp"
#include "declval.hpp"
#include "forward.hpp"
#include "functional/functor.hpp"
#include "functional/id.hpp"
#include "functional/map_arguments.hpp"
#include "tuple_apply.hpp"

namespace PP
{
	constexpr inline auto tuple_map = map_arguments(tuple_apply,
		[](auto&& map)
		{
			return [&map](auto&&... elements) -> decltype(auto)
			{
				return tuple<decltype(declval<decltype(map)>()(declval<decltype(elements)>()))...>
					(PP_FORWARD(map)(PP_FORWARD(elements))...);
			};
		}, id_forward);

	constexpr decltype(auto) operator*(const functor<auto>& f, tuple_like auto&& tuple)
	{
		return tuple_map(f.f, PP_FORWARD(tuple));
	}
	constexpr decltype(auto) operator*(const functor<auto>&& f, tuple_like auto&& tuple)
	{
		return tuple_map(std::move(f).f, PP_FORWARD(tuple));
	}
}
