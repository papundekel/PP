#pragma once
#include "view.hpp"

namespace PP
{
	constexpr auto find(concepts::view auto&& v, auto&& p)
	{
		auto i = view_begin(v);
		for (; i != view_end(v) && !PP_F(p)(*i); ++i)
			;
		return i;
	}
}
