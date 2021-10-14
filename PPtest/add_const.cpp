#include <iostream>

#include "PP/add_const.hpp"

namespace PPtest
{
void add_const()
{
    std::cout << std::boolalpha
              << (PP::type<const int> == PP::add_const(PP::type<int>)) << '\n';
}
}
