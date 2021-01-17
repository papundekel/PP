#pragma once
#include "declval.hpp"
#include "tuple_count.hpp"
#include "tuple_element.hpp"
#include "tuple_get.hpp"
#include "tuple_index_sequence_for.hpp"
#include "type_t.hpp"
#include "value_t.hpp"

namespace PP
{
	namespace detail
	{
		template <typename T, std::size_t... I>
		concept tuple_like_helper_helper = requires
		{
			((void)tuple_get(value_v<I>, declval(type_v<T>)), ...);
			((void)tuple_element(value_v<I>, declval(type_v<T>)), ...);
		};

		template <typename T, std::size_t... I>
		requires tuple_like_helper_helper<T, I...>
		constexpr void tuple_like_helper(std::index_sequence<I...>) noexcept {}
	}

	template <typename T>
	concept tuple_like = requires (type_t<T> t)
	{
		tuple_count(declval(t));
		detail::tuple_like_helper<T>(tuple_index_sequence_for(declval(t)));
	};
}
