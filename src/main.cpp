#include "output.hpp"
#include "fundamental.hpp"
#include "make_const.hpp"
#include "same.hpp"
#include "decrementable.hpp"
#include "block.hpp"
#include "make_integer_unsigned.hpp"
#include "make_cv.hpp"

int main()
{
	print(same<const unsigned int, make_integer_unsigned<const unsigned int>>::v);

	return 0;
}