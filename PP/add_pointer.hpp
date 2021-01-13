#pragma once
#include "functional/functor.hpp"
#include "concepts/pointable.hpp"

namespace PP
{
	PP_FUNCTOR(add_pointer, auto t)
	{
		using T = PP_GET_TYPE(t);

		if constexpr (concepts::pointable<T>)
			return type_v<T*>;
		else
			return t;
	}};
}
