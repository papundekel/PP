#pragma once
#include "declval.hpp"
#include "get_type.hpp"
#include "macros/simple_concept.hpp"
#include "tuple_count.hpp"
#include "tuple_get.hpp"
#include "tuple_element.hpp"
#include "tuple_value_sequence_for.hpp"
#include "value_t.hpp"

namespace PP
{
	namespace detail
	{
		template <auto... I>
		constexpr void tuple_like_helper(concepts::type auto t, value_sequence<I...>) noexcept
		requires requires
		{
			((void)::PP::tuple_get    (::PP::value<I>, ::PP::declval(t)), ...);
			((void)::PP::tuple_element(::PP::value<I>, ::PP::declval(t)), ...);
		};
	}

	PP_FUNCTOR(is_tuple, concepts::type auto t)
	{
		return requires
		{
			::PP::tuple_count_value_t(declval(t));
			::PP::detail::tuple_like_helper(t, tuple_value_sequence_for(declval(t)));
		};
	});

	PP_CONCEPT1(tuple)
}
