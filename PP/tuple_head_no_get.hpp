#pragma once
#include "functional/functor.hpp"

namespace PP
{
	namespace detail
	{
		template <typename T>
		concept tuple_concept_head_no_get_member = requires
		{
			declval(type<T>).head();
		};
		template <typename T>
		concept tuple_concept_head_no_get_any =
			tuple_concept_head_no_get_member<T> || requires
		{
			head_implementation(declval(type<T>));
		};
	}

	PP_FUNCTOR(tuple_head_no_get,
			   detail::tuple_concept_head_no_get_any auto&& t) -> decltype(auto)
	{
		if constexpr (detail::tuple_concept_head_no_get_member<decltype(t)>)
			return PP_FORWARD(t).head();
		else
			return head_implementation(PP_FORWARD(t));
	});
}
