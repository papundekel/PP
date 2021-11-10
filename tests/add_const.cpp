#include "PP/add_const.hpp"

#include <iostream>

void test(std::ostream& out_key, std::ostream& out_run)
{
    out_key << "true";
    //
    out_run << std::boolalpha
            << (PP::type<const int> == PP::add_const(PP::type<int>));
}
