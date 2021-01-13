#pragma once
#include <type_traits>
#include <utility>

#include "declval.hpp"
#include "tuple_size.hpp"
#include "type_t.hpp"
#include "value_t.hpp"

namespace PP
{
	namespace detail
	{
		template <typename T, std::size_t... I>
		concept tuple_like_helper_helper = requires
		{
			((void)get(value_t<I>{}, declval(type_v<T>)), ...);
		};

		template <typename T, std::size_t... I>
		requires tuple_like_helper_helper<T, I...>
		constexpr void tuple_like_helper(std::index_sequence<I...>) noexcept {}
	}

	template <typename T>
	concept tuple_like = requires
	{
		tuple_type_size(type_v<T>);
		detail::tuple_like_helper<T>(std::make_index_sequence<tuple_type_size(type_v<T>)>{});
	};
}
