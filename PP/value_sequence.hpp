#pragma once
#include "get_value.hpp"

namespace PP
{
	template <auto... I>
	struct value_sequence
	{
		constexpr auto append(concepts::value auto j) noexcept
		{
			return value_sequence<I..., PP_GET_VALUE(j)>{};
		}
	};

	namespace detail
	{
		constexpr auto make_value_sequence(concepts::value auto i)
		{
			if constexpr (PP_GET_VALUE(i) == 0)
				return value_sequence<>{};
			else
				return make_value_sequence(i - value_1).append(i - value_1);
		}
	}

	PP_FUNCTOR(make_value_sequence, concepts::value auto i)
	{
		return detail::make_value_sequence(i);
	}};
}
