#pragma once
template <typename it1, typename it2, typename test>
it2 copy_backward_if(it1 srcBegin, it1 srcEnd, it2 destEnd, test t)
{
	while (srcEnd != srcBegin)
		if (t(*(--srcEnd)))
			*(--destEnd) = *srcEnd;
	return destEnd;
}