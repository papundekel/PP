#include "output_basic.hpp"

char* copy_char(char* begin, char* end, char c)
{
	*begin = c;
	return ++begin;
}

char to_char(unsigned char digit)
{
	return (digit < 10 ? '0' : 'A' - 10) + digit;
}