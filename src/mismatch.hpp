#pragma once
template <typename it1, typename it2>
pair<it1, it2> mismatch(it1 first_begin, it1 first_end, it2 second_begin)
{
	for (; first_begin != first_end && *first_begin == *second_begin; ++first_begin, ++second_begin);
	return { first_begin, second_begin };
}