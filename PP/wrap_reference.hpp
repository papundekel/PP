#pragma once
#include "concepts/reference.hpp"
#include "reference_wrapper.hpp"

namespace PP
{
	PP_FUNCTOR(wrap_reference, concepts::type auto t)
	{
		constexpr auto T = PP_COPY_TYPE(t);

		if constexpr (is_reference(T))
			return type<reference_wrapper<PP_GET_TYPE(!t), is_rvalue_reference(T)>>;
		else
			return t;
	}};
}