#include "output.hpp"
#include "pack.hpp"
#include "empty_class.hpp"
#include "declval.hpp"
#include "pointer_type.hpp"
#include "class_type.hpp"
#include "is_constant_evaluated.hpp"
#include "accumulate.hpp"
#include "move_.hpp"
#include "void_t.hpp"
#include "ignore_type.hpp"
#include "array.hpp"

int main()
{
	int a[] = { 1, 4, 5, 6 };

	print(accumulate(a));

	return 0;
}