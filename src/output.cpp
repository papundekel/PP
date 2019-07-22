#include "output.hpp"

void print(char c)
{
	std::putchar(c);
}

void print(const char* cstring)
{
	std::puts(cstring);
}