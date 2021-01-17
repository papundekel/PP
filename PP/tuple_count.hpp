#pragma once
#include "decl_type.hpp"
#include "declval.hpp"
#include "functional/apply_partially.hpp"
#include "functional/functor.hpp"
#include "get_value.hpp"

namespace PP
{
	namespace detail
	{
		constexpr auto tuple_count_member(auto&& t)
		requires requires { { PP_FORWARD(t).tuple_count() } -> value_wrap; }
		{
			return PP_FORWARD(t).tuple_count();
		}
		constexpr auto tuple_count_nonmember(auto&& t)
		requires requires { { tuple_count_implementation(PP_FORWARD(t)) } -> value_wrap; }
		{
			return tuple_count_implementation(PP_FORWARD(t));
		}

		PP_FUNCTOR(tuple_count_value_t, auto&& t)
		{
			if constexpr (requires { tuple_count_member(PP_FORWARD(t)); })
				return tuple_count_member(PP_FORWARD(t));
			else
				return tuple_count_nonmember(PP_FORWARD(t));
		}};
	}
	
	PP_FUNCTOR(tuple_count, auto&& t)
	requires (
		requires { detail::tuple_count_member(PP_FORWARD(t)); } ||
		requires { detail::tuple_count_nonmember(PP_FORWARD(t)); })
	{
		return (get_value | detail::tuple_count_value_t)(PP_FORWARD(t));
	}};

	PP_FUNCTOR(call_get_value_declval, auto&& f, type_wrap auto t)
	{
		return PP_GET_VALUE(PP_FORWARD(f)(declval(t)));
	}};

	constexpr inline auto tuple_type_count = call_get_value_declval(partial_tag, detail::tuple_count_value_t);
}
