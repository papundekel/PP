#pragma once
#include "iterator.hpp"

namespace PP
{
	template <typename I>
	concept has_base = iterator<I> &&
		requires (I i)
	{
		{ i.base() } -> iterator;
	};

	constexpr iterator auto base(iterator auto i)
	{
		return i;
	}
	constexpr iterator auto base(has_base auto i)
	{
		return i.base();
	}
}
