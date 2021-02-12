#pragma once
#include "cv_qualifier.hpp"
#include "functional/compose.hpp"
#include "is_const.hpp"
#include "is_volatile.hpp"
#include "remove_reference.hpp"
#include "value_t.hpp"

namespace PP
{
	constexpr inline auto get_cv_value_t = functor{ []
	(concepts::type auto t)
	{
		constexpr auto T = PP_COPY_TYPE(t);

		return value<
			(is_const(T) ? cv_qualifier::Const : cv_qualifier::none) |
			(is_volatile(T) ? cv_qualifier::Volatile : cv_qualifier::none)>;
	}} | remove_reference;
}
