#pragma once
#include "view.hpp"

namespace Papo
{
	constexpr iterator auto find(view auto&& v, auto p)
	{
		auto i = begin(v);
		for (; i != end(v) && !p(*i); ++i);
		return i;
	}
}
