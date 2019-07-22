#pragma once
#include <cstdio>
#include "range.hpp"
#include "integer.hpp"
#include "mem_mov.hpp"
#include "mem_cpy.hpp"
#include "mem_set.hpp"
#include "callable.hpp"
#include "cstring.hpp"
#include "floating.hpp"
#include "almost.hpp"

#define _output(function, value) (begin = (function)(begin, end, (value)))

class output_error{};

char* copy_char(char* begin, char* end, char c);

template <size_t size>
constexpr char* copy_chars(char* begin, char* end, const char(&s)[size])
{
	if (end - begin >= size * sizeof(char))
		return reinterpret_cast<char*>(mem_cpy(s, begin, size - 1)) + size - 1;
	else
		throw output_error();
}

char to_char(unsigned char digit);

template <typename T>
char* to_chars(char* begin, char* end, T value)
{
	if constexpr (bool(integer<T>))
	{
		auto old_end = end;
		--end;
		if (value == 0 && end >= begin)
			*end = '0';
		else
		{
			bool minus = false;
			if (value < 0)
			{
				minus = true;
				value = -value;
			}
			for (; end >= begin && value != 0; --end)
			{
				*end = to_char(value % 10);
				value /= 10;
			}
			if (end >= begin && minus)
				*end = '-';
			else
				++end;
		}

		auto count = old_end - end;
		mem_mov(end, begin, count);
		return begin + count;
	}
	else if constexpr (bool(almost<T, bool>))
		return value ? _output(copy_chars, "true") : _output(copy_chars, "false");
	else if constexpr (bool(floating<remove_cvref<T>>))
	{
		snprintf(begin, end - begin, "%f", value);
		return ::end(begin);
	}

	return nullptr;
}

template <size_t size>
char* to_chars(char(&buffer)[size], const auto& x)
{
	return to_chars(buffer, buffer + size, x);
}

template <typename T>
concept printable = requires(char (&buffer)[], T x)
{
	{ to_chars(buffer, x) } -> char*;
};

template <size_t max_size = 256>
size_t output_length(const auto& x)
{
	char buffer[max_size];
	return range(buffer, to_chars(buffer, x)).count();
}