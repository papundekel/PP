#pragma once
#include "../functional/functor.hpp"
#include "../get_type.hpp"
#include "complete_object.hpp"
#include "unbounded_array.hpp"

namespace PP
{
	namespace concepts
	{
		template <typename T>
		concept object = complete_object<T> || unbounded_array<T>;
	}

	PP_FUNCTOR(is_object, type_wrap auto t)
	{
		return concepts::object<PP_GET_TYPE(t)>;
	}};
}
