#include "output.hpp"
#include "list.hpp"
#include "constructible.hpp"
#include "convertible.hpp"
#include "add_const.hpp"
#include "const_t.hpp"
#include "apply.hpp"
#include "equals.hpp"
#include "find.hpp"
#include "bim.hpp"
#include "any_of.hpp"
#include "all_of.hpp"
#include "callable.hpp"
#include "remove.hpp"

int main()
{
	int arr[] = {1, 3, 5, 7, 4, 5, 1, 9};
	print(*find(range(arr), [](int x){ return x % 2 == 0; }));

	return 0;
}