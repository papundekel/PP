#pragma once
#include "../functional/functor.hpp"
#include "../get_type.hpp"
#include "same.hpp"

namespace PP
{
	namespace concepts
	{
		template <typename T>
		concept void_type =
			same<T, 			   void> ||
			same<T, const 		   void> ||
			same<T, 	  volatile void> ||
			same<T, const volatile void>;

		template <typename T>
		concept nonvoid = !void_type<T>;
	}

	PP_FUNCTOR(is_void, concepts::type auto t)
	{
		return concepts::void_type<PP_GET_TYPE(t)>;
	});
}
