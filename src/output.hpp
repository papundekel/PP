#pragma once
#include "output_basic.hpp"
#include "range.hpp"
#include "apply.hpp"

void print(char c);
void print(const char* cstring);

template <size_t s>
void print(const char(&buffer)[s])
{
	std::puts(buffer);
}

template <size_t buffer_size = 256>
void print(const auto& x)
{
	char buffer[buffer_size];
	*to_chars(buffer, x) = 0;
	print(buffer);
}

template <typename R>
requires range_type<R>::v
void print(R r)
{
	apply(r, [](const auto& x) { print(x); });
}