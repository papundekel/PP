#pragma once
template <typename it1, typename it2>
it1 search(it1 firstBegin, it1 firstEnd, it2 secondBegin, it2 secondEnd)
{
	for (; (firstBegin = find(firstBegin, firstEnd, *secondBegin)) != firstEnd && !equal(secondBegin, secondEnd, firstBegin); ++firstBegin);
	return firstBegin;
}