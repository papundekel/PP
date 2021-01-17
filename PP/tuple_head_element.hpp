#pragma once
#include "functional/functor.hpp"

namespace PP
{
	namespace detail
	{
		constexpr auto tuple_head_element_member(auto&& t)
		requires requires { { PP_FORWARD(t).head_element() } -> type_wrap; }
		{
			return PP_FORWARD(t).head_element();
		}
		constexpr auto tuple_head_element_nonmember(auto&& t)
		requires requires { { head_element_implementation(PP_FORWARD(t)) } -> type_wrap; }
		{
			return head_element_implementation(PP_FORWARD(t));
		}
	}

	PP_FUNCTOR(tuple_head_element, auto&& t)
	requires
		requires { detail::tuple_head_element_member(PP_FORWARD(t)); } ||
		requires { detail::tuple_head_element_nonmember(PP_FORWARD(t)); }
	{
		if constexpr (requires { detail::tuple_head_element_member(PP_FORWARD(t)); })
			return detail::tuple_head_element_member(PP_FORWARD(t));
		else
			return detail::tuple_head_element_nonmember(PP_FORWARD(t));
	}};
}
