#pragma once
#include <cstdio>
#include <cctype>
#include "cstring.hpp"
class input_error {};

template <size_t s>
char* read(char (&buffer)[s])
{
	int c;
	do 
		c = std::getchar();
	while (std::isspace(c) && c != EOF);

	char* i = buffer;
	do
	{
		*i++ = c;
		c = std::getchar();
	} while (!std::isspace(c) && c != EOF && i != end(buffer));
	
	return i;
}

char* read(char* buffer, size_t length);