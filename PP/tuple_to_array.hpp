#pragma once
#include "array.hpp"
#include "get_type.hpp"
#include "tuple_apply.hpp"
#include "tuple_count.hpp"
#include "tuple_element.hpp"
#include "tuple_like.hpp"

namespace PP
{
	namespace detail
	{
		constexpr auto tuple_first_element_or(concepts::type auto t, concepts::tuple auto&& tuple)
		{
			if constexpr (tuple_type_count(PP_DECLTYPE(tuple)) != 0)
				return tuple_element(value_0, PP_FORWARD(tuple));
			else
				return t;
		}

		constexpr auto tuple_to_array_implementation(concepts::type auto t, concepts::tuple auto&& tuple)
		{
			if constexpr (PP_COPY_TYPE(t) == type_void)
				return tuple_to_array_implementation(tuple_first_element_or(type_char, PP_FORWARD(tuple)), PP_FORWARD(tuple));
			else
				return functor{ []
					(auto&&... args)
					{
						return PP::array<PP_GET_TYPE(t), tuple_type_count(PP_DECLTYPE(tuple))>{ PP_FORWARD(args)... };
					}}[PP_FORWARD(tuple)];
		}
	}
	
	PP_FUNCTOR(tuple_to_array, concepts::type auto t, concepts::tuple auto&& tuple)
	{
		return detail::tuple_to_array_implementation(t, PP_FORWARD(tuple));
	}};

	constexpr auto operator&(concepts::type auto t, concepts::tuple auto&& tuple)
	{
		return tuple_to_array(t, PP_FORWARD(tuple));
	}
	constexpr auto operator&(concepts::tuple auto&& tuple)
	{
		return tuple_to_array(type_void, PP_FORWARD(tuple));
	}
}
