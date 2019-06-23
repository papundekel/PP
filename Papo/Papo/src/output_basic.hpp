#pragma once
#include <cstdio>
#include "integral.hpp"
#include "distance.hpp"
#include "mem_mov.hpp"
#include "mem_cpy.hpp"

#define _output(function, value) begin = (function)(begin, end, (value))
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

template <integral I>
char* to_chars(char* begin, char* end, I value)
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

template <almost<bool> B>
char* to_chars(char* begin, char* end, B b)
{
	return b ? _output(copy_chars, "true") : _output(copy_chars, "false");
}

char* to_chars(char* begin, char* end, float f);
char* to_chars(char* begin, char* end, double d);

template <size_t size, typename T>
char* to_chars(char(&buffer)[size], const T& x)
{
	return to_chars(buffer, buffer + size, x);
}

template <typename T>
concept printable = requires(char (&buffer)[], T x)
{
	{ to_chars(buffer, x) } -> char*;
};

template <size_t max_size = 256, typename T>
size_t output_length(const T& x)
{
	char buffer[max_size];
	return distance(range(buffer, to_chars(buffer, x)));
}