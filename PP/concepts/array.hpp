#pragma once
#include "bounded_array.hpp"
#include "unbounded_array.hpp"

namespace PP
{
	namespace concepts
	{
		template <typename T>
		concept array = bounded_array<T> || unbounded_array<T>;
	}

	PP_FUNCTOR(is_array, type_wrap auto t)
	{
		return concepts::array<PP_GET_TYPE(t)>;
	}};
}
