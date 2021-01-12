#pragma once
#include "complete_object.hpp"
#include "returnable.hpp"

namespace PP
{
	namespace concepts
	{
		template <typename T>
		concept bounded_array = complete_object<T> && !returnable<T>;
	}

	PP_FUNCTOR(is_bounded_array, auto t)
	{
		return concepts::bounded_array<PP_GET_TYPE(t)>;
	}};
}
