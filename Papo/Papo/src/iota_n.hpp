#pragma once
template <typename it, typename T>
void iota_n(it begin, size_t count, T value)
{
	for (size_t i = 0; i != count; ++i, ++begin, ++value)
		* begin = value;
}