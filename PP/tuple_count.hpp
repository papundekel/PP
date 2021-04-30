#pragma once
#include "decl_type.hpp"
#include "declval.hpp"
#include "functional/compose.hpp"
#include "functional/functor.hpp"
#include "get_value.hpp"

namespace PP
{
	namespace detail
	{
		template <typename T>
		concept tuple_concept_count_value_t_member = requires
		{
			{
				::PP::declval(::PP::type<T>).tuple_count()
			}
			->concepts::value;
		};
		template <typename T>
		concept tuple_concept_count_value_t_any =
			tuple_concept_count_value_t_member<T> || requires
		{
			{
				tuple_count_implementation(::PP::declval(::PP::type<T>))
			}
			->concepts::value;
		};
	}

	PP_FUNCTOR(tuple_count_value_t,
			   detail::tuple_concept_count_value_t_any auto&& t)
	{
		if constexpr (detail::tuple_concept_count_value_t_member<decltype(t)>)
			return PP_FORWARD(t).tuple_count();
		else
			return tuple_count_implementation(PP_FORWARD(t));
	});

	PP_FUNCTOR(tuple_type_count_value_t, concepts::type auto t)
	{
		return PP_COPY_VALUE(tuple_count_value_t(declval(t)));
	});

	constexpr inline auto tuple_count = get_value | tuple_count_value_t;
	constexpr inline auto tuple_type_count =
		get_value | tuple_type_count_value_t;
}
