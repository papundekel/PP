#pragma once
#include "../functional/functor.hpp"
#include "referencable.hpp"

namespace PP
{
	PP_FUNCTOR(is_reference, auto t)
	{
		return is_referencable(t) && (t == t + rvalue_tag);
	}};

	namespace concepts
	{
		template <typename T>
		concept reference = is_reference(type_v<T>);
	}
}
