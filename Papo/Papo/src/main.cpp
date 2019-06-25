#include "output.hpp"
#include "list.hpp"
#include "bim.hpp"
#include "accumulate.hpp"
#include "iota.hpp"
#include "find.hpp"
#include "copyable.hpp"
#include "convertible.hpp"
#include "integer.hpp"

int main()
{
	print(number_signed<int>);
	print(number_signed<float>);
	print(number_signed<unsigned int>);

	return 0;
}