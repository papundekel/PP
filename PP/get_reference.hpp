#pragma once
#include "concepts/reference.hpp"
#include "functional/compose.hpp"
#include "ref_qualifier.hpp"
#include "remove_reference.hpp"
#include "value_t.hpp"

namespace PP
{
	PP_FUNCTOR(get_reference_value_t, concepts::type auto t)
	{
		constexpr auto T = PP_COPY_TYPE(t);

		if constexpr (is_lvalue_reference(T))
			return value<ref_qualifier::lvalue>;
		else if constexpr (is_rvalue_reference(T))
			return value<ref_qualifier::rvalue>;
		else
			return value<ref_qualifier::none>;
	}};
}
