#pragma once
template <typename it1, typename it2, typename test>
it2 copy_n_if(it1 srcBegin, size_t count, it2 destBegin, test t)
{
	for (size_t i = 0; i != count; ++i, ++destBegin, ++srcBegin)
		if (t(*srcBegin))
			*destBegin = *srcBegin;
	return destBegin;
}