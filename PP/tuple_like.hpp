#pragma once
#include <tuple>
#include <utility>
#include <type_traits>
#include "type_t.hpp"

namespace PP
{
	namespace detail
	{
		template <typename T, std::size_t... I>
		struct tuple_like_helper
		{
			constexpr tuple_like_helper(PP::type_t<T>, std::index_sequence<I...>) {}

			static constexpr bool v = requires
			{
				((void)std::get<I>(std::declval<T>()), ...);
			};
		};
	}

	template <typename T>
	concept tuple_like = requires
	{
		std::tuple_size<std::remove_reference_t<T>>::value;
	} && detail::tuple_like_helper(PP::type_v<T>, std::make_index_sequence<std::tuple_size<std::remove_reference_t<T>>::value>{}).v;
}
