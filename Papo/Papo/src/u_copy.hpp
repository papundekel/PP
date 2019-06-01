#pragma once
#include "enable_if.hpp"
#include "is_iterator.hpp"
#include "construct.hpp"

template <typename it1, typename it1_end, typename it2>
it2 u_copy(range<it1, it1_end> src, it2 destBegin)
{
	for (; src.begin != src.end; ++destBegin, ++src.begin)
		construct(destBegin, *src.begin);
	return destBegin;
}


template <typename it1, typename it1_end, typename it2, typename it2_end>
it2 u_copy(range<it1, it1_end> src, range<it2, it2_end> dest)
{
	for (; src.begin != src.end; ++dest.begin, ++src.begin)
		construct(dest.begin, *src.begin);
	return dest.begin;
}