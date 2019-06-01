#pragma once
template <typename it1, typename it2>
it2 move_n(it1 srcBegin, size_t count, it2 destBegin)
{
	for (size_t i = 0; i != count; ++i, ++destBegin, ++srcBegin)
		*destBegin = std::move(*srcBegin);
	return destBegin;
}