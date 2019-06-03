#pragma once
#include <cstdio>
#include <cstring>
#include "integral.hpp"
#include "distance.hpp"

#define _output(function, value) begin = (function)(begin, end, (value))
class output_error{};

char* copy_char(char* begin, char* end, char c);

char to_char(unsigned char digit);

template <integral I>
char* to_chars(char* begin, char* end, I value, int base = 10)
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
			*end = to_char(value % base);
			value /= base;
		}
		if (end >= begin && minus)
			*end = '-';
		else
			++end;
	}

	auto count = old_end - end;
	memmove(begin, end, count);
	return begin + count;
}

template <size_t size>
constexpr char* copy_chars(char* begin, char* end, const char(&s)[size])
{
	if (end - begin >= size * sizeof(char))
		return reinterpret_cast<char*>(memcpy(begin, s, size - 1)) + size - 1;
	else
		throw output_error();
}

char* to_chars(char* begin, char* end, bool b);
char* to_chars(char* begin, char* end, float b);
char* to_chars(char* begin, char* end, double b);

template <typename T>
concept printable = requires (char* begin, char* end, T x)
{
    { to_chars(begin, end, x) } -> char*;
};

template <size_t size, printable T>
char* to_chars(char(&buffer)[size], const T& x)
{
	return to_chars(buffer, buffer + size, x);
}

template <size_t max_size = 256, printable T>
size_t output_length(const T& x)
{
	char buffer[max_size];
	return distance(range(buffer, to_chars(buffer, x)));
}