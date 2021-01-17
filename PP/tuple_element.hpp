#pragma once
#include "copy_cv.hpp"
#include "decl_type.hpp"
#include "declval.hpp"
#include "functional/apply_partially.hpp"
#include "functional/functor.hpp"
#include "get_value.hpp"
#include "tuple_recursive.hpp"
#include "tuple_head_element.hpp"

namespace PP
{
	namespace detail
	{
		constexpr auto tuple_element_member(value_wrap auto i, auto&& t)
		requires requires { { PP_FORWARD(t).element(i) } -> type_wrap; }
		{
			return PP_FORWARD(t).element(i);
		}
		constexpr auto tuple_element_nonmember(value_wrap auto i, auto&& t)
		requires requires { { element_implementation(i, PP_FORWARD(t)) } -> type_wrap; }
		{
			return element_implementation(i, PP_FORWARD(t));
		}
		constexpr auto tuple_element_recursive(value_wrap auto i, auto&& t)
		requires requires { { tuple_recursive(tuple_head_element, i, PP_FORWARD(t)) } -> type_wrap; }
		{
			return tuple_recursive(tuple_head_element, i, PP_FORWARD(t));
		}

		PP_FUNCTOR(tuple_element_no_cv, value_wrap auto i, auto&& t)
		{
			if constexpr (requires { tuple_element_member(i, PP_FORWARD(t)); })
				return tuple_element_member(i, PP_FORWARD(t));
			else if constexpr (requires { tuple_element_nonmember(i, PP_FORWARD(t)); })
				return tuple_element_nonmember(i, PP_FORWARD(t));
			else
				return tuple_element_recursive(i, PP_FORWARD(t));
		}};
	}

	PP_FUNCTOR(tuple_element, value_wrap auto i, auto&& t)
	requires
		requires { detail::tuple_element_member(i, PP_FORWARD(t)); } ||
		requires { detail::tuple_element_nonmember(i, PP_FORWARD(t)); } ||
		requires { detail::tuple_element_recursive(i, PP_FORWARD(t)); }
	{
		return copy_cv(PP_DECLTYPE(t), detail::tuple_element_no_cv(i, PP_FORWARD(t)));
	}};
	
	PP_FUNCTOR(tuple_type_element, value_wrap auto i, type_wrap auto t)
	{
		return PP_COPY_TYPE(tuple_element(i, declval(t)));
	}};
}
