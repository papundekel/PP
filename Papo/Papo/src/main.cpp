#include "output.hpp"
#include "block.hpp"
#include "u_fill.hpp"
#include "list.hpp"

int main()
{
	block<list<int>> b(10);
	u_fill(range(b), 10, 10, 6);

	for (auto x : b)
	{
		print(x);
		print("-------");
	}
	return 0;
}