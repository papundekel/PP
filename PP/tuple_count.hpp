#pragma once
#include "compose.hpp"
#include "decl_type.hpp"
#include "declval.hpp"
#include "declval_impl.hpp"
#include "functor.hpp"
#include "get_value.hpp"

namespace PP
{
	namespace detail
	{
		template <typename T>
		concept tuple_concept_count_value_t_member = requires
		{
			{
				::PP::declval_impl<T>().tuple_count()
				} -> concepts::value;
		};
		template <typename T>
		concept tuple_concept_count_value_t_any =
			tuple_concept_count_value_t_member<T> || requires
		{
			{
				tuple_count_impl(::PP::declval_impl<T>())
				} -> concepts::value;
		};
	}

	PP_FUNCTOR(tuple_count_value_t,
	           detail::tuple_concept_count_value_t_any auto&& t)
	{
		if constexpr (detail::tuple_concept_count_value_t_member<decltype(t)>)
			return PP_F(t).tuple_count();
		else
			return tuple_count_impl(PP_F(t));
	});

	PP_FUNCTOR(tuple_type_count_value_t, concepts::type auto t)
	{
		return PP_COPY_VALUE(tuple_count_value_t(declval(t)));
	});

	constexpr inline auto tuple_count = get_value | tuple_count_value_t;
	constexpr inline auto tuple_type_count =
		get_value | tuple_type_count_value_t;
}
