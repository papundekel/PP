#include <iostream>
#include <vector>

#include "value_sequence.hpp"

template <auto... I>
void f(PP::value_sequence<I...>)
{
	((std::cout << I), ...);
}

int main()
{
	[[maybe_unused]] auto x = PP::make_value_sequence(PP::value<11>);

	f(x);

	std::cout.flush();
	return 0;
}
