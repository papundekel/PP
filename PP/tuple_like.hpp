#pragma once
#include <utility>
#include <type_traits>
#include "value_t.hpp"

namespace PP
{
	namespace detail
	{
		template <typename T, std::size_t... I>
		concept tuple_like_helper_helper = requires
		{
			((void)get(value_t<I>{}, std::declval<T>()), ...);
		};

		template <typename T, std::size_t... I>
		requires tuple_like_helper_helper<T, I...>
		constexpr void tuple_like_helper(std::index_sequence<I...>) noexcept {}
	}

	template <typename T>
	concept tuple_like = requires
	{
		std::tuple_size<std::remove_reference_t<T>>::value;
		detail::tuple_like_helper<T>(std::make_index_sequence<std::tuple_size<std::remove_reference_t<T>>::value>{});
	};
}
