#pragma once
#include "output_basic.hpp"
#include "range.hpp"

template <size_t s>
void print(const char(&buffer)[s])
{std::puts(buffer);}

void print(char c);
void print(const char* cstring);

template <size_t buffer_size = 256, typename T>
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
auto print(R r)
{
	for (; r.begin != r.end; ++r.begin)
		print(*r.begin);
	return r.begin;
}