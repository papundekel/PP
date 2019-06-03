#include "output.hpp"
#include "block.hpp"
#include "u_fill.hpp"
#include "list.hpp"
#include "input.hpp"

bool f(char c)
{
	return std::isspace(c);
}

int main()
{
	char buffer[100];
	range r(buffer);

	r.end = read(buffer, [](char c) {return c == '\n'; });
	*r.end = 0;

	auto x = split(r, f);

	print(x);

	return 0;
}