#pragma once
#include "functional/functor.hpp"

namespace PP
{
	namespace detail
	{
		constexpr  decltype(auto) tuple_head_no_get_member(auto&& t)
		requires requires { PP_FORWARD(t).head(); }
		{
			return PP_FORWARD(t).head();
		}
		constexpr decltype(auto) tuple_head_no_get(auto&& t)
		requires requires { head_implementation(PP_FORWARD(t)); }
		{
			return head_implementation(PP_FORWARD(t));
		}
	}

	PP_FUNCTOR(tuple_head_no_get, auto&& t) -> decltype(auto)
	requires
		requires { detail::tuple_head_no_get_member(PP_FORWARD(t)); } ||
		requires { detail::tuple_head_no_get(PP_FORWARD(t)); }
	{
		if constexpr (requires { detail::tuple_head_no_get_member(PP_FORWARD(t)); })
			return detail::tuple_head_no_get_member(PP_FORWARD(t));
		else
			return detail::tuple_head_no_get(PP_FORWARD(t));
	}};
}
