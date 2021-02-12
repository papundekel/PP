#include <iostream>
#include <vector>

#include "any_iterator.hpp"
#include "unbounded.hpp"

int main()
{
	int arr[] = { 1, 2 };
	auto begin = PP::make_any_iterator(PP::view_begin(arr));
	auto end = PP::make_any_iterator(PP::view_end(arr));

	for (auto i = begin; i != end; ++i)
	{
		std::cout << *i << '\n';
	}

	std::cout.flush();
	return 0;
}
