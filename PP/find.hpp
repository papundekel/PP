#pragma once
#include "view.hpp"

namespace PP
{
constexpr auto find(concepts::view auto&& v, auto&& p)
{
	auto i = view::begin(v);
	for (; i != view::end(v) && !PP_F(p)(*i); ++i)
		;
	return i;
}
}
