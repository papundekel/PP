#pragma once
#include "../functional/functor.hpp"
#include "atomic/user_defined.hpp"
#include "class.hpp"

namespace PP
{
	namespace concepts
	{
		template <typename T>
		concept enum_type = atomic::user_defined<T> && !class_type<T>;
	}

	PP_FUNCTOR(is_enum_type, type_wrap auto t)
	{
		return concepts::enum_type<PP_GET_TYPE(t)>;
	}};
}
