#pragma once
#include <cstdio>
#include <cctype>
#include "cstring.hpp"
#include "callable.hpp"

class input_error {};

template <size_t s, callable_r<bool, char> P = decltype(std::isspace(0))(int)>
char* read(char (&buffer)[s], P&& p = std::isspace)
{
	int c;
	do 
		c = std::getchar();
	while (c != EOF && p(c));

	char* i = buffer;
	do
	{
		*i++ = c;
		c = std::getchar();
	} while (i != end(buffer) && c != EOF && !p(c));
	
	return i;
}

char* read(char* buffer, size_t length);