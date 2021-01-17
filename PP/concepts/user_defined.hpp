#pragma once
#include "../functional/functor.hpp"
#include "../get_type.hpp"
#include "class.hpp"
#include "enum.hpp"

namespace PP
{
	namespace concepts
	{
		template <typename T>
		concept user_defined = atomic::user_defined<T> ||
			class_type<T> ||
			enum_type<T>);
	}

	PP_FUNCTOR(is_user_defined, type_wrap auto t)
	{
		return concepts::user_defined<PP_GET_TYPE(t)>;
	}};
}
