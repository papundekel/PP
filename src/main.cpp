#include "output.hpp"
#include "find.hpp"

int main()
{
	int arr[] = { 1, 4, 5, 6 };
	print(!!find(range_n(arr), 6));
	
	return 0;
}