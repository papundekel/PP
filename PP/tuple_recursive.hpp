#pragma once
#include "get_value.hpp"
#include "tuple_count.hpp"
#include "tuple_pred.hpp"
#include "value_t_static_cast.hpp"

namespace PP
{
	namespace detail
	{
		constexpr decltype(auto) tuple_recursive(auto&& f,
		                                         concepts::value auto i,
		                                         auto&& t)
		{
			if constexpr (*PP_COPY_VALUE(i) == 0)
				return PP_F(f)(PP_F(t));
			else
				return tuple_recursive(PP_F(f),
				                       i - value_1,
				                       tuple_pred(PP_F(t)));
		}
	}

	// clang-format off
	PP_FUNCTOR(tuple_recursive, auto&& f, concepts::value auto i, auto&& t)
		-> decltype(auto)
		requires
			requires { PP_F(f)(PP_F(t)); }
		&&	(
				*PP_COPY_VALUE(i) == 0
			||	requires { tuple_pred(PP_F(t)); }
			)
		&&	(bool(PP_COPY_VALUE(i) < tuple_type_count_value_t(PP_DECLTYPE(t))))
	{
		return detail::tuple_recursive(PP_F(f), i, PP_F(t));
	});
	// clang-format on
}
