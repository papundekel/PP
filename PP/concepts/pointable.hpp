#pragma once
#include "../functional/functor.hpp"
#include "../get_type.hpp"
#include "../templated_dummy.hpp"

namespace PP
{
	PP_FUNCTOR(is_pointable, auto t)
	{
		return requires
		{
			typename detail::templated_dummy<PP_GET_TYPE(t)*>;
		};
	}};

	namespace concepts
	{
		template <typename T>
		concept pointable = is_pointable(type_v<T>);
	}
}
