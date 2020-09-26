#include <iostream>
#include "array.hpp"
#include "tuple_get_value_from_key.hpp"
#include "sizeof_v.hpp"
#include "type_tuple.hpp"
#include "tuple_map.hpp"
#include "tuple_zip.hpp"
#include "tuple_for_each.hpp"

struct X
{
	int x;
	X(int x) : x(x) {}
	X(const X&) { std::cout << "copied\n"; }
	X(X&&) { std::cout << "moved\n"; }
	X& operator=(const X&) = default;
	X& operator=(X&&) = default;
};

template <typename T>
struct A { T x; };

int main()
{
	PP::tuple_for_each<>
		([](auto&& p)
		{
			auto [type, id] = std::move(p);
			std::cout << PP::sizeof_v(type) << " : " << id.x << '\n';
		})
		(PP::tuple_zip(std::forward_as_tuple(PP::type_tuple_v<A<int>, A<double>, A<char>>, std::array{ X{1}, X{4}, X{7} })));
	
	std::cout.flush();
	return 0;
}
