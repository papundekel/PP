#pragma once
#include "declval.hpp"
#include "iterator.hpp"
#include "type_t.hpp"

namespace PP
{
	constexpr auto iterator_inner(concepts::iterator auto i)
	{
		if constexpr (requires { { i.inner_iterator() } -> concepts::iterator; })
			return i.inner_iterator();
		else
			return i;
	}
}
