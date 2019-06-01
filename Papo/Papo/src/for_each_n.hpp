#pragma once
template <typename it, typename function>
void for_each_n(it begin, size_t count, function f)
{
	for (size_t i = 0; i != count; ++i, ++begin)
		f(*begin);
}