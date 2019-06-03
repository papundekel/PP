#include "output.hpp"
#include "input.hpp"
#include "accumulate.hpp"

int main()
{
	int arr[] = { 1, 4, 5, 65, 1 };
	print(accumulate(range(arr)));

	return 0;
}