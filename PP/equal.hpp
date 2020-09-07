#pragma once
#include "view.hpp"

namespace PP
{
	template <view View1, view View2>
	constexpr bool equal(View1&& v1, View2&& v2)
	{
		auto i = begin(std::forward<View1>(v1));
		auto j = begin(std::forward<View2>(v2));
		for (; i != end(std::forward<View1>(v1)) && j != end(std::forward<View2>(v2)); ++i, ++j)
			if (*i != *j)
				return false;
		return i == end(std::forward<View1>(v1)) && j == end(std::forward<View2>(v2));
	}
}
