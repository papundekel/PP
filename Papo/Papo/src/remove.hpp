#pragma once
#include "enable_if.hpp"
#include "is_function.hpp"
#include "find.hpp"
#include "move.hpp"

template <typename it, typename T>
enable_if<!is_function<T>,
it> remove(it begin, it end, const T& value)
{
	auto first = find(begin, end, value);
	for (auto i = first; i != end; ++i)
		if (*i != value)
		{
			*first = move(*i);
			++first;
		}
	return first;
}