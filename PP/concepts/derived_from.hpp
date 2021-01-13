#pragma once
#include "class.hpp"
#include "convertible_to.hpp"

namespace PP
{
	namespace concepts
	{
		template <typename D, typename B>
		concept derived_from = class_type<D> && class_type<B> && convertible_to<const volatile D*, const volatile B*>;
	}

	PP_FUNCTOR(is_derived_from, auto t)
	{
		return concepts::derived_from<PP_GET_TYPE(t)>;
	}
};
}
