#pragma once
#include "apply_pack.hpp"
#include "apply_partially.hpp"
#include "tuple_get_element.hpp"
#include "tuple_value_sequence_for.hpp"
#include "type_tuple.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_type_get_types, concepts::type auto t)
	{
		return apply_pack(make_type_tuple,
		                  tuple_type_get_element(partial_tag, value_1, t),
		                  tuple_type_value_sequence_for(t));
	});
	PP_FUNCTOR(tuple_get_types, concepts::tuple auto&& t)
	{
		return tuple_type_get_types(PP_DECLTYPE(t));
	});
}
