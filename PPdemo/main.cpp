#include <iomanip>
#include <iostream>
#include <vector>
#include <variant>

#include "PP/any_iterator.hpp"
#include "PP/concepts/fundamental.hpp"
#include "PP/view_subsequence.hpp"
#include "PP/tuple_concat.hpp"

int main()
{
	auto x = PP::tuple_concats(PP::make_tuple(PP::type_tuple<int>, PP::type_tuple<double, char>));

	[[maybe_unused]] int a = !x;

	std::cout.flush();
	return 0;
}
