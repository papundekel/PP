#pragma once
#include "../declval.hpp"
#include "../functor.hpp"
#include "convertible_to.hpp"

namespace PP
{
PP_FUNCTOR(is_equatable, concepts::type auto a, concepts::type auto b)
{
	return requires
	{
		{
			PP::declval(a) == PP::declval(b)
			} -> concepts::convertible_to<bool>;
	};
});
}

namespace PP::concepts
{
template <typename T, typename U>
concept equatable = is_equatable(PP::type<T>, PP::type<U>);
}
