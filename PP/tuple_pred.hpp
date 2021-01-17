#pragma once
#include "functional/functor.hpp"

namespace PP
{
	namespace detail
	{
		constexpr decltype(auto) tuple_pred_member(auto&& t)
		requires requires { PP_FORWARD(t).pred(); }
		{
			return PP_FORWARD(t).pred();
		}
		constexpr decltype(auto) tuple_pred(auto&& t)
		requires requires { pred_implementation(PP_FORWARD(t)); }
		{
			return pred_implementation(PP_FORWARD(t));
		}
	}

	PP_FUNCTOR(tuple_pred, auto&& t) -> decltype(auto)
	requires (
		requires { detail::tuple_pred_member(PP_FORWARD(t)); } ||
		requires { detail::tuple_pred(PP_FORWARD(t)); })
	{
		if constexpr (requires { detail::tuple_pred_member(PP_FORWARD(t)); })
			return detail::tuple_pred_member(PP_FORWARD(t));
		else
			return detail::tuple_pred(PP_FORWARD(t));
	}};
}
