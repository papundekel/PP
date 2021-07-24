#include <iostream>

#include "ostream_std.hpp"

namespace PP
{
constinit static ostream_std cout_obj(std::cout);

ostream& cout = cout_obj;
}
