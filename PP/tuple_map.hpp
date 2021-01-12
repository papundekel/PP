#pragma once
#include <tuple>
#include <type_traits>

#include "declval.hpp"
#include "forward.hpp"
#include "functional/functor.hpp"
#include "functional/id.hpp"
#include "functional/map_arguments.hpp"
#include "tuple_apply.hpp"

namespace PP
{
	constexpr inline auto tuple_map =
		
	/*[](auto&& f, auto&& tuple)
	{
		return tuple_apply([&f](auto&&... elements) -> decltype(auto)
			{
				return std::tuple<decltype(std::declval<decltype(f)>()(std::declval<decltype(elements)>()))...>
					(PP_FORWARD(f)(PP_FORWARD(elements))...);
			}, PP_FORWARD(tuple));
	};*/
	
	map_arguments(tuple_apply,
	[](auto&& map)
	{
		return [&map](auto&&... elements) -> decltype(auto)
		{
			return std::tuple<decltype(declval<decltype(map)>()(declval<decltype(elements)>()))...>
				(PP_FORWARD(map)(PP_FORWARD(elements))...);
		};
	}
	, id_weak);

	constexpr decltype(auto) operator*(const functor<auto>& f, tuple_like auto&& tuple)
	{
		return tuple_map(f.f, PP_FORWARD(tuple));
	}
	constexpr decltype(auto) operator*(const functor<auto>&& f, tuple_like auto&& tuple)
	{
		return tuple_map(std::move(f).f, PP_FORWARD(tuple));
	}
}
