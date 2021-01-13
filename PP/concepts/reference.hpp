#pragma once
#include "../functional/functor.hpp"
#include "returnable.hpp"
#include "complete_object.hpp"
#include "void.hpp"

namespace PP
{
	namespace concepts
	{
		template <typename T>
		concept reference = returnable<T> && nonvoid<T> && incomplete_object<T>;
	}

	PP_FUNCTOR(is_reference, auto t)
	{
		return concepts::reference<PP_GET_TYPE(t)>;
	}};
}
