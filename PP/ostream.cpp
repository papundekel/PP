#include "ostream_std.hpp"

#include <iostream>

namespace PP
{
constinit static ostream_std cout_obj(std::cout);

ostream& cout = cout_obj;
}
