#pragma once
#include "remove_volatile.hpp"
#include "same.hpp"

namespace PP
{
	PP_FUNCTOR(is_volatile, concepts::type auto t)
	{
		return remove_volatile(t) != t;
	});
}
