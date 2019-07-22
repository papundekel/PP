#include "cstring.hpp"
#include "find.hpp"
#include "equals.hpp"

char* begin(char*& cstring)
{
	return cstring;
}
char* end(char*& cstring)
{
	return find(range(cstring, cstring_end()), 0).begin;
}

const char* begin(const char*& cstring)
{
	return cstring;
}
const char* end(const char*& cstring)
{
	return end(const_cast<char*&>(cstring));
}