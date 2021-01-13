#pragma once
#include "decl_type.hpp"
#include "functional/functor.hpp"
#include "remove_cvref.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_type_size, auto t)
	{
		return size_implementation(remove_cvref(t));
	}};

	constexpr inline auto tuple_size = tuple_type_size | decl_type;
}
