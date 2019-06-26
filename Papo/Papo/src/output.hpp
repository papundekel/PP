#pragma once
#include "output_basic.hpp"
#include "range.hpp"

template <size_t s>
void print(const char(&buffer)[s])
{std::puts(buffer);}

void print(char c);
void print(const char* cstring);

template <typename T, size_t buffer_size = 256>
void print(const T& x)
{
	if constexpr (container<T> && !printable<T>)
		for (const auto& i : x)
			print(i);
	else
	{
		char buffer[buffer_size];
		*to_chars(buffer, x) = 0;
		print(buffer);
	}
}

template <range_t R>
void print(R r)
{
	for (; r; ++r)
		print(*r);
}