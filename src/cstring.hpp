#pragma once
#include "int.hpp"
struct cstring_end {};

constexpr bool operator==(const char* left, cstring_end)
{
	return *left == 0;
}
constexpr bool operator!=(const char* left, cstring_end)
{
	return *left != 0;
}

char* begin(char*& cstring);
char* end(char*& cstring);
const char* begin(const char*& cstring);
const char* end(const char*& cstring);

template <size_t size>
constexpr auto begin(char(&arr)[size])
{
	return arr;
}
template <size_t size>
constexpr auto end(char(&arr)[size])
{
	return arr + size;
}
template <size_t size>
constexpr auto begin(const char(&arr)[size])
{
	return arr;
}
template <size_t size>
constexpr auto end(const char(&arr)[size])
{
	return arr + size;
}