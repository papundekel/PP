#include "output.hpp"
#include "list.hpp"
#include "bim.hpp"

int main()
{
	list<int> l = range({ 1, 4, 7 });
	print(l);
	return 0;
}