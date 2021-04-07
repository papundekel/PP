#include <iomanip>
#include <iostream>
#include <vector>
#include <variant>

#include "PP/any_iterator.hpp"
#include "PP/concepts/fundamental.hpp"
#include "PP/view_subsequence.hpp"

int main()
{
	int a[] = {1, 2, 3, 4, 5};
	int b[] = {1, 4, 5};
	int c[] = {2, 3, 4, 5};

	std::cout << PP::view_subsequence(b, a) << PP::view_subsequence(c, a);

	std::cout.flush();
	return 0;
}
