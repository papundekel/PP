#include "output.hpp"
#include "find.hpp"

int main()
{
	int arr[] = { 1, 4, 5, 6 };
	print(!!find(range(arr), 2));

	return 0;
}