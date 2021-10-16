#include <iostream>

#include "PP/add_const.hpp"

namespace PPtest
{
void add_const(std::ostream& out_key, std::ostream& out_run)
{
    out_key << "true";
    //
    out_run << std::boolalpha
            << (PP::type<const int> == PP::add_const(PP::type<int>));
}
}
