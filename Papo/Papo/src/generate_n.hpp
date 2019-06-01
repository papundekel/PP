#pragma once
template <typename it, typename generator>
void generate_n(it begin, size_t count, generator g)
{
	for (size_t i = 0; i != count; ++i, ++begin)
		* begin = g();
}