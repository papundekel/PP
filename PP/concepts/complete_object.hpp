#pragma once
#include "../functional/functor.hpp"
#include "../get_type.hpp"
#include "../templated_dummy.hpp"

namespace PP
{
	PP_FUNCTOR(is_complete_object, auto t)
	{
		return requires
		{
			typename detail::templated_dummy<PP_GET_TYPE(t)[]>;
		};
	}};

	namespace concepts
	{
		template <typename T>
		concept complete_object = is_complete_object(type_v<T>);
	}
}
