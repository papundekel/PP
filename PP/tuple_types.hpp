#pragma once
#include "apply_pack.hpp"
#include "apply_partially.hpp"
#include "tuple_element.hpp"
#include "tuple_value_sequence_for.hpp"
#include "type_tuple.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_types, concepts::type auto t)
	{
		return apply_pack(make_type_tuple,
		                  tuple_type_element(partial_tag, value_1, t),
		                  tuple_type_value_sequence_for(t));
	});
}
