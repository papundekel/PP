#pragma once
#include "declval.hpp"
#include "get_value.hpp"
#include "tuple_concept.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_type_get_element,
	           concepts::value auto i,
	           concepts::type auto t)
	{
		return PP_DECLTYPE(declval(t)[i]);
	});
	PP_FUNCTOR(tuple_get_element,
	           concepts::value auto i,
	           concepts::tuple auto&& t)
	{
		return tuple_type_get_element(i, PP_DECLTYPE(t));
	});
}
