#include "output.hpp"
#include "list.hpp"
#include "constructible.hpp"
#include "convertible.hpp"

int main()
{
	list<int> l = range{ 1, 55, 4, 7, 85 };

	print(l);

	return 0;
}