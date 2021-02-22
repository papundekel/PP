#pragma once
#include "concepts/reference.hpp"
#include "reference_wrapper.hpp"

namespace PP
{
	PP_FUNCTOR(wrap_reference, concepts::type auto t)
	{
		if constexpr (is_reference(PP_COPY_TYPE(t)))
			return type<reference_wrapper<PP_GET_TYPE(t)>>;
		else
			return t;
	});
}