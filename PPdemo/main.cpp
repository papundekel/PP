#include <iomanip>
#include <iostream>
#include <vector>

#include "PP/concepts/fundamental.hpp"

int main()
{
	std::cout << PP::is_floating_point(PP::type<float>);

	std::cout.flush();
	return 0;
}
