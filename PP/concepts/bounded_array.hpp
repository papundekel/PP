#pragma once
#include "atomic/complete_object.hpp"
#include "atomic/returnable.hpp"

namespace PP
{
	namespace concepts
	{
		template <typename T>
		concept bounded_array = atomic::complete_object<T> && !returnable<T>;
	}

	PP_FUNCTOR(is_bounded_array, type_wrap auto t)
	{
		return concepts::bounded_array<PP_GET_TYPE(t)>;
	}};
}
