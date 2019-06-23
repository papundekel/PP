#include "output_basic.hpp"

static constexpr char* find_end(char* begin)
{
	for (; *begin != 0; ++begin);
	return begin;
}

char* copy_char(char* begin, char* end, char c)
{
	if (end - begin > 0)
	{
		*begin = c;
		return ++begin;
	}
	else
		throw output_error();
}

char to_char(unsigned char digit)
{
	return (digit < 10 ? '0' : 'A' - 10) + digit;
}

char* to_chars(char* begin, char* end, float f)
{
	snprintf(begin, end - begin, "%f", f);
	return find_end(begin);
}
char* to_chars(char* begin, char* end, double d)
{
	snprintf(begin, end - begin, "%f", d);
	return find_end(begin);
}