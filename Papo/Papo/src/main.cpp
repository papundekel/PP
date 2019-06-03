#include "output.hpp"
#include "input.hpp"
#include "adjacent_find.hpp"

int main()
{
	int arr[] = { 1, 4, 5, 65, 1, 1 };
	range r(arr);
	print(adjacent_find(r) != r.end);

	return 0;
}