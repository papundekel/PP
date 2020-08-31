#pragma once
#include <utility>
#include "view.hpp"

namespace PP
{
	template <view View, typename Predicate>
	constexpr bool any_of(View&& v, Predicate&& p)
	{
		for (auto&& e : std::forward<View>(v))
			if (std::forward<Predicate>(p)(e))
				return true;
		return false;
	}
}
