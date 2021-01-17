#pragma once
#include "../functional/functor.hpp"
#include "../get_type.hpp"
#include "../declval.hpp"

namespace PP
{
	PP_FUNCTOR(is_convertible_to, auto from, auto to)
	{
		return requires
		{
			[](PP_GET_TYPE(to)){}(declval(from));
		};
	}};
	namespace concepts
	{
		template <typename From, typename To>
		concept convertible_to = is_convertible_to(type_v<From>, type_v<To>);
	}
}
