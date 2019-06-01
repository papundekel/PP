#pragma once
template <typename it1, typename it2, typename test>
it2 copy_backward_n_if(size_t count, it1 srcEnd, it2 destEnd, test t)
{
	for (size_t i = 0; i != count; ++i)
		if (t(*(--srcEnd)))
			*(--destEnd) = *srcEnd;
	return destEnd;
}