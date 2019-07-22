#pragma once
template <typename it>
it min_element(it begin, it end)
{
	if (begin == end)
		return end;
	auto min = begin;
	while (++begin != end)
		if (*begin < *min)
			min = begin;
	return min;
}