#pragma once
#include "range.hpp"
#include "is_callable.hpp"

template <typename it1, typename it1_end, typename it2, typename test>
it2 copy_if(it1 srcBegin, it1 srcEnd, it2 destBegin, test t)
{
	static_assert(is_callable<bool, test, base_type<it1>>);

	for (; srcBegin != srcEnd; ++destBegin, ++srcBegin)
		if (t(*srcBegin))
			*destBegin = *srcBegin;
	return destBegin;
}

template <typename it1, typename it1_end, typename it2, typename it2_end, typename test>
it2 copy_if(range<it1, it2> src, range<it2, it2_end> dest, test t)
{
	static_assert(is_callable<bool, test, base_type<it1>>);

	for (; src.begin != src.end; ++dest.begin, ++src.begin)
		if (t(*src.begin))
			* dest.begin = *src.begin;
	return dest.begin;
}