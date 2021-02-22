#pragma once
#include "../add_reference.hpp"
#include "../macros/simple_concept.hpp"
#include "atomic/referencable.hpp"
#include "same.hpp"

namespace PP
{
	constexpr inline auto is_lvalue_reference = is_referencable && functor([]
		(concepts::type auto t)
		{
			return t + add_lvalue_tag == t;
		});

	PP_CONCEPT1(lvalue_reference)
}
