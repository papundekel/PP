#include <iostream>
#include <vector>

#include "zip_view.hpp"
#include "array.hpp"
#include "simple_vector.hpp"
#include "array_ostream.hpp"

int main()
{
	PP::array_ostream<32> stream;
	PP::simple_ostream& out = stream;

	out.write("cigi");

	out.write_to_ostream(std::cout);

	std::cout.flush();
	return 0;
}
