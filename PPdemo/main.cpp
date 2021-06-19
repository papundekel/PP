#include <iomanip>
#include <iostream>
#include <variant>
#include <vector>

#include "PP/array_vector.hpp"
#include "PP/max_default.hpp"
#include "PP/simple_vector.hpp"
#include "PP/size_of.hpp"
#include "PP/small_optimized_vector.hpp"
#include "PP/tuple_cartesian_product.hpp"
#include "PP/tuple_map_to_array.hpp"
#include "PP/variant.hpp"

void f(auto x, auto y)
{
	std::cout << sizeof(x) << ' ' << sizeof(y) << '\n';
	std::cout << x << ' ' << y << '\n';
}

int main()
{
	auto table =
		PP::applier(
			[](auto t, auto u) -> void (*)(const void*, const void*)
			{
				return [](const void* x, const void* y)
				{
					f(*reinterpret_cast<const PP_GET_TYPE(t)*>(x),
					  *reinterpret_cast<const PP_GET_TYPE(u)*>(y));
				};
			}) <
		PP::tuple_cartesian_product_pack(PP::type_tuple<char, short, int>,
										 PP::type_tuple<float, double>);

	short x = 4;
	float y = 2.4;
	table[2](&x, &y);

	std::cout.flush();
	return 0;
}
