#pragma once
template <typename it1, typename it2>
auto copy_n(it1 srcBegin, size_t count, it2 destBegin)
{
	for (size_t i = 0; i != count; ++i, ++destBegin, ++srcBegin)
		*destBegin = *srcBegin;
	return destBegin;
}