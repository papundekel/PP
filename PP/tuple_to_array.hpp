#pragma once
#include "array.hpp"
#include "conditional.hpp"
#include "get_type.hpp"
#include "tuple_apply.hpp"
#include "tuple_concept.hpp"
#include "tuple_count.hpp"
#include "tuple_element.hpp"

namespace PP
{
	namespace detail
	{
		constexpr auto tuple_first_element_or(concepts::type auto t,
		                                      concepts::tuple auto&& tuple)
		{
			if constexpr (tuple_type_count(PP_DECLTYPE(tuple)) != 0)
				return tuple_element(value_0, PP_F(tuple));
			else
				return t;
		}

		constexpr auto tuple_to_array_helper(concepts::type auto t,
		                                     concepts::tuple auto&& tuple)
		{
			return conditional(value<PP_COPY_TYPE(t) == type_void>,
			                   tuple_first_element_or(type_char, PP_F(tuple)),
			                   t);
		}
	}

	PP_FUNCTOR(tuple_to_array,
	           concepts::type auto t,
	           concepts::tuple auto&& tuple)
	{
		return (array_constructor_typed * value_false *
		        detail::tuple_to_array_helper(t, PP_F(tuple)))[PP_F(tuple)];
	});

	constexpr auto operator&(concepts::type auto t,
	                         concepts::tuple auto&& tuple)
	{
		return tuple_to_array(t, PP_F(tuple));
	}
	constexpr auto operator&(concepts::tuple auto&& tuple)
	{
		return tuple_to_array(type_void, PP_F(tuple));
	}
}
