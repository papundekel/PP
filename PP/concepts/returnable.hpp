#pragma once
#include "../functional/functor.hpp"
#include "../get_type.hpp"
#include "../templated_dummy.hpp"

namespace PP
{
	namespace detail
	{
		template <typename T>
		T templated_return_dummy_function();
	}

	PP_FUNCTOR(is_returnable, auto t)
	{
		return requires
		{
			detail::templated_return_dummy_function<PP_GET_TYPE(t)>();
		};
	}};

	namespace concepts
	{
		template <typename T>
		concept returnable = is_returnable(type_v<T>);
	}
}
