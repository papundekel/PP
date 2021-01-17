#include <iostream>
#include <vector>

#include "remove_cvref.hpp"
#include "pointer_stack.hpp"
#include "tuple.hpp"
#include "array.hpp"

#include "tuple_fold.hpp"

#include "tuple_count.hpp"
#include "tuple_element.hpp"
#include "tuple_get.hpp"

#include "generator_tuple.hpp"
#include "template_tuple.hpp"
#include "type_tuple.hpp"
#include "view_tuple.hpp"
#include "functional/id.hpp"

struct S
{
	S() = default;
	constexpr S(const S&)
	{
		std::cout << "copied\n";
	}
	constexpr S(S&&)
	{
		std::cout << "moved\n";
	}
};

int main()
{
	const std::vector<int> v = { 1, 2, 4, 6 };
	
	auto t = PP::generator_tuple<PP::id_copy>();

	decltype(auto) c = PP::tuple_count(t);
	decltype(auto) e = PP::tuple_element(PP::value_0, t);
	decltype(auto) g = PP::tuple_get(PP::value_1, t);

	std::cout.flush();
	return 0;
}
