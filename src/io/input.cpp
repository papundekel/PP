#include <cstdio>
#include <cctype>

char* read(char* buffer, size_t length)
{
	int c;
	do
		c = std::getchar();
	while (std::isspace(c));

	char* i = buffer;
	while (c != EOF && i != buffer + length)
	{
		*i++ = c;
		c = std::getchar();
	}

	return i;
}