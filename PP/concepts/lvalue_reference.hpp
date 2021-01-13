#pragma once
#include "reference.hpp"
#include "same.hpp"

namespace PP
{
	namespace concepts
	{
		template <typename T>
		concept lvalue_reference = reference<T> && same<T, T&>;
	}

	PP_FUNCTOR(is_lvalue_reference, auto t)
	{
		return concepts::lvalue_reference<PP_GET_TYPE(t)>;
	}};
}
