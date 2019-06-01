#pragma once
template <typename it1, typename it2>
it1 find_first_of(it1 begin, it1 end, it2 sub_begin, it2 sub_end)
{
	for (; begin != end && find(sub_begin, sub_end, *begin) == sub_end; ++begin);
	return begin;
}