#pragma once
#include "int.hpp"
struct cstring_end {};

bool operator==(const char* left, cstring_end);
bool fff(const char* left, cstring_end);

char* begin(char* cstring);
char* end(char* cstring);
const char* begin(const char* cstring);
const char* end(const char* cstring);