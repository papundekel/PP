#include <iostream>
#include <vector>
#include <tuple>
#include "zip_with.hpp"

void f(int a, int b)
{
	std::cout << a << "->" << b << '\n';
}

int main()
{
	std::vector<int> a = { 1, 5, 7, 4 };

	std::vector<int> b = { 5, 7, 53, 4, 9 };

	Papo::zip_with(f, a, b);

	std::cout.flush();
	return 0;
}
