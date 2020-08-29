#pragma once
#include <utility>

template <typename Range, typename Predicate>
constexpr bool any_of(Range&& r, Predicate&& p)
{
	for (auto&& e : std::forward<Range>(r))
		if (std::forward<Predicate>(p)(e))
			return true;
	return false;
}
