#include "output.hpp"
#include "list.hpp"
#include "bim.hpp"
#include "accumulate.hpp"
#include "iota.hpp"
#include "find.hpp"
#include "copyable.hpp"
#include "convertible.hpp"

int main()
{
	int arr[] = { 1, 5, 4, 54, 12, 1, 4 };
	int rra[7];
	copy(range(arr), range(rra));
	print(rra);

	return 0;
}