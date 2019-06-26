#pragma once
#include "output_basic.hpp"
#include "range.hpp"

void print(char c);
void print(const char* cstring);

template <size_t s>
void print(const char(&buffer)[s])
{
	std::puts(buffer);
}

template <typename T, size_t buffer_size = 256>
void print(const T& x)
{
	char buffer[buffer_size];
	*to_chars(buffer, x) = 0;
	print(buffer);
}