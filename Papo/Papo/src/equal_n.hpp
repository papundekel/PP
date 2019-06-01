#pragma once
template <typename it1, typename it2>
bool equal_n(it1 first_begin, size_t count, it2 second_begin)
{
	for (size_t i = 0; i != count; ++i, ++first_begin, ++second_begin)
		if (*first_begin != *second_begin)
			return false;
	return true;
}