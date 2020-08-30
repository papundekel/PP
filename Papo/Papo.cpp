#include <iostream>
#include <vector>
#include <tuple>
#include "any_of.hpp"
#include "transform_view.hpp"



int main()
{
	std::vector<int> v = { 1, 5, 4, 6 };

	for (auto&& x : v | Papo::transform([](const auto& x) { return x * 2; }))
		std::cout << x << '\n';



	std::cout.flush();
	return 0;
}
