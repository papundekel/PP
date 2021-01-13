#pragma once
#include <type_traits>
#include "cv_qualifier.hpp"
#include "functional/id.hpp"
#include "tuple_get_value_from_key.hpp"
#include "value_t.hpp"

namespace PP
{
	PP_FUNCTOR(add_cv, auto cv, auto t)
	{
		return tuple_get_value_from_key();
	}};
}
