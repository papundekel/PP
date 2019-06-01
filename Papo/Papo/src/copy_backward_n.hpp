#pragma once
template <typename it1, typename it2>
it2 copy_backward_n(size_t count, it1 srcEnd, it2 destEnd)
{
	for (size_t i = 0; i != count; ++i)
		*(--destEnd) = *(--srcEnd);
	return destEnd;
}