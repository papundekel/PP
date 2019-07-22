#pragma once
#include "enable_if.hpp"
#include "is_container.hpp"

template <typename container>
enable_if<is_container<container>,
bool> palindrome(const container& c)
{
	if constexpr (is_iterator_bi<iterator<container>>)
	{
		for (auto i = c.begin(), j = prev(c.end()); i != j && next(i) != j; ++i, --j)
			if (*i != *j)
				return false;
		return true;
	}
	else
	{
		array<
	}
}