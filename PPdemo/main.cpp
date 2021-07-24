#include <iostream>

#include "PP/tuple/for_each.hpp"
#include "PP/tuple/zip_with.hpp"

int main()
{
	PP::tuple_zip_with_pack(
		[](auto x, auto y)
		{
			std::cout << x << y << '\n';
			return 0;
		},
		PP::make_tuple(0, 1, 2, 3, 4),
		PP::make_tuple(0, 1, 2, 3, 4));

	return 0;
}
