#pragma once
template <typename it, typename test>
size_t count_if(it begin, it end, test t)
{
	size_t result = 0;
	for (; begin != end; ++begin)
		if (t(*begin))
			++result;
	return result;
}