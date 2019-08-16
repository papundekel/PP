#include "output.hpp"
#include "pack.hpp"
#include "empty_class.hpp"
#include "declval.hpp"
#include "pointer_type.hpp"
#include "class_type.hpp"
#include "is_constant_evaluated.hpp"
#include "accumulate.hpp"
#include "move_.hpp"
#include "ignore_type.hpp"
#include "array.hpp"
#include "is_type.hpp"

int main()
{
	print(floating<bool>::v);

	return 0;
}