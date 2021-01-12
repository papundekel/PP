#pragma once
#include "../functional/functor.hpp"
#include "../get_type.hpp"
#include "../declval.hpp"
#include "../templated_dummy.hpp"

namespace PP
{
	PP_FUNCTOR(is_class, auto t)
	{
		return requires
		{
			typename detail::templated_dummy<int PP_GET_TYPE(t)::*>;
		};
	}
};
namespace concepts
{
	template <typename T>
	concept class_type = is_class(type_v<T>);
}
}
