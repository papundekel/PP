#pragma once
#include "block.hpp"
#include "u_copy.hpp"
#include "next.hpp"
#include "output.hpp"

template <range_t R, callable_r<bool, range_base<R>> P>
auto split(R r, P p)
{
	using T = range_base<R>;

	size_t x = 1;

	for (auto i = r.begin; i != r.end; ++i)
	{
		if (p(*i))
			++x;
	}

	block<block<T>> arrays(x);
	range s(arrays);

	x = 0;

	for (range t(r.begin, r.begin); t.end != r.end; ++t.end)
	{
		if (!p(*t.end))
			++x;
		else
		{
			construct(s.begin, x);
			u_copy(t, range(*s.begin));
			t.begin = next(t.end);
			x = 0;
		}
	}

	return arrays;
}