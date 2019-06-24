#include "output.hpp"
#include "list.hpp"
#include "bim.hpp"

int main()
{
	int arr[] = { 11, 5, 7, 6, 4, 4 };
	int arr2[6];
	copy(range(arr), range(arr2));
	print(arr2);

	return 0;
}