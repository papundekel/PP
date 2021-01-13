#pragma once
#include "../functional/functor.hpp"
#include "../get_type.hpp"
#include "../declval.hpp"

namespace PP
{
	PP_FUNCTOR(is_convertible_to, auto f, auto t)
	{
		return requires
		{
			[](PP_GET_TYPE(t)){}(declval(f));
		};
	}};
	namespace concepts
	{
		template <typename F, typename T>
		concept convertible_to = is_convertible_to(type_v<F>, type_v<T>);
	}
}
