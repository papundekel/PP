#pragma once
template <typename it1, typename it2>
it2 copy_backward(it1 srcBegin, it1 srcEnd, it2 destEnd)
{
	while (srcEnd != srcBegin)
		*(--destEnd) = *(--srcEnd);
	return destEnd;
}