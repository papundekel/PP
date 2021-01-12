#pragma once
#include "tuple_split.hpp"

namespace PP
{
	namespace detail
	{
		struct tuple_foldr_helper
		{
			constexpr decltype(auto) operator()(auto&& f, auto&& init, tuple_like auto&& tuple) const
			{
				auto split = tuple_split(std::forward<decltype(tuple)>(tuple));
				if constexpr (tuple_like<decltype(split)>)
					return std::forward<decltype(f)>(f)(
						tuple_get<0>(std::move(split)),
						(*this)(std::forward<decltype(f)>(f), std::forward<decltype(init)>(init), tuple_get<1>(std::move(split))));
				else
					return std::forward<decltype(init)>(init);
			}
		};
	}

	constexpr inline auto tuple_foldr = detail::tuple_foldr_helper{};

	constexpr inline auto tuple_foldr1 =
		[](auto&& f, tuple_like auto&& tuple)
		{
			auto split = tuple_split(std::forward<decltype(tuple)>(tuple));
			return tuple_foldr(std::forward<decltype(f)>(f), tuple_get<0>(std::move(split)), tuple_get<1>(std::move(split)));
		};
}