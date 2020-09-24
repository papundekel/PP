#include <iostream>
#include "array.hpp"
#include "tuple_get_value_from_key.hpp"
#include "sizeof_v.hpp"
#include "type_tuple.hpp"
#include "tuple_map.hpp"
#include "tuple_zip.hpp"

/*namespace PP
{
	template <typename Tuples>
	constexpr auto cartesian_product(Tuples tuples)
	{

	}
}*/


struct X
{
	X() = default;
	X(const X&) { std::cout << "copied\n"; }
	X(X&&) { std::cout << "moved\n"; }
};

int main()
{
	auto types = PP::type_tuple_v<int, double>;
	auto values = std::array{ 4, 8 };

	auto p = std::forward_as_tuple(types, values);

	auto zipped = PP::tuple_zip(p);

	std::cout.flush();
	return 0;
}
