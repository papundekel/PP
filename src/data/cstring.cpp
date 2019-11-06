#include "cstring.hpp"
#include "find.hpp"

bool operator==(const char* left, cstring_end a)
{
	return fff(left, a);
}

bool fff(const char* left, cstring_end)
{
	return *left == 0;
}

char* begin(char* cstring)
{
	return cstring;
}
char* end(char* cstring)
{
	return cstring;//+find(range(cstring, cstring_end{}), 0);
}

const char* begin(const char* cstring)
{
	return cstring;
}
const char* end(const char* cstring)
{
	return end(const_cast<char*>(cstring));
}