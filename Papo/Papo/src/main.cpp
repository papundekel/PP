#include "output.hpp"
#include "input.hpp"
#include "block.hpp"
#include "bim.hpp"
#include "u_fill.hpp"
#include "split.hpp"
#include "list.hpp"

int main()
{
	list<bim<>, 10> bla = { 1, 2, 3, 0, 1, 2, 3, 4, 0, 1 };
	range r(bla);

	auto a = split(r, [](const bim<>& i) { return i == 0; });

	for (auto& i : a)
		print(i);

	return 0;
}