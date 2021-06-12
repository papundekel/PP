#include <iomanip>
#include <iostream>
#include <variant>
#include <vector>

#include "PP/array_vector.hpp"
#include "PP/simple_vector.hpp"
#include "PP/small_optimized_vector.hpp"

struct noisy
{
	noisy() = default;
	noisy(noisy&&)
	{
		std::cout << "MOVED!\n";
	}
	~noisy()
	{
		std::cout << "JAU!\n";
	}
};

int main()
{
	PP::small_optimized_vector<noisy, 4> x;
	x.push_back();
	x.push_back();
	x.push_back();
	x.push_back();
	x.push_back();

	// auto y = PP::move(x);

	std::cout << x.count() << '\n';
	// std::cout << y.count() << '\n';

	std::cout.flush();
	return 0;
}
