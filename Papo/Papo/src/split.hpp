#pragma once
#include "block.hpp"

template <range_t R, callable_r<bool, typename R::base_t> P>
auto split(R r, P&& p)
{
	using T = typename R::base_t;

	list<list<T>> arrays;
	list<T> arr;

	for (; r.begin != r.end; ++r.begin)
	{
		if (!p(*r.begin))
			arr.push_back(*r.begin);
		else
		{
			arrays.push_back(move(arr));
			arr = list<T>();
		}
	}

	return arrays;
}