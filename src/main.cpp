#include "output.hpp"
#include "list.hpp"
#include "constructible.hpp"
#include "convertible.hpp"
#include "add_const.hpp"
#include "const.hpp"
#include "apply.hpp"
#include "equals.hpp"
#include "find.hpp"
#include "bim.hpp"
#include "any_of.hpp"
#include "all_of.hpp"
#include "callable.hpp"
#include "remove.hpp"
#include "const.hpp"
#include "byte.hpp"
#include <type_traits>

int main()
{
	block<int> a(3);
	u_fill(range(a), 5);
	block<ref<int>> b(a.count());
	u_generate(range(b), [&a]()->auto&{ static size_t i = 0; return a[i++]; });
	for (auto x : b)
		x = 4;
	print(range(a));

	int x = 9;
	ref r = x;
	r = 8;
	print(x);
	return 0;
}