#pragma once
#include "decl_type.hpp"
#include "functional/functor.hpp"
#include "remove_cvref.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_type_element, auto t)
	{
		return element_implementation(remove_cvref(t));
	}};

	constexpr inline auto tuple_element = tuple_type_size | decl_type;
}
