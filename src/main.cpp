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
#include "is_template.hpp"
#include "is_template_nontype.hpp"
#include "same_template.hpp"
#include "fundamental.hpp"
#include "trait_test.hpp"
#include "make_const.hpp"
#include "block.hpp"
#include "list.hpp"
#include "split.hpp"
#include "size_of.hpp"

int main()
{
	print(same<int, remove_const<const int>>::v);
	return 0;
}