#pragma once
#include "../functional/functor.hpp"
#include "../declval.hpp"
#include "convertible_to.hpp"

namespace PP
{
	PP_FUNCTOR(is_equatable, auto a, auto b)
	{
		return requires
		{
			{ declval(a) == declval(b) } -> concepts::convertible_to<bool>;
		};
	}};

	namespace concepts
	{
		template <typename T, typename U>
		concept equatable = is_equatable(type_v<T>, type_v<U>);
	}
}