#include <iostream>
#include <vector>

#include "PP/array.hpp"
#include "PP/negate.hpp"
#include "PP/static_block.hpp"
#include "PP/tuple.hpp"
#include "PP/tuple_apply.hpp"
#include "PP/tuple_map.hpp"
#include "PP/tuple_to_array.hpp"

struct S
{
	S(int)
	{
		std::cout << "int\n";
	}
	S(bool)
	{
		std::cout << "bool\n";
	}
	S(const S&) = delete;
	S(S&&) = delete;
};

int main()
{
	auto t = PP::make_tuple();

	auto arr = PP::tuple_to_array(PP::type<void>, t);

	for (auto&& x : arr)
		std::cout << x << '\n';

	int x = arr;

	std::cout.flush();
	return 0;
}
