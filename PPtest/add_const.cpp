#include "PP/add_const.hpp"
#include "PPtest.hpp"

#include <iostream>

namespace PPtest
{
template<> std::string_view test_function_name<0>() { return __FILE__; }

template<>
void test_function<0>(std::ostream& out_key, std::ostream& out_run)
{
    out_key << "true";
    //
    out_run << std::boolalpha
            << (PP::type<const int> == PP::add_const(PP::type<int>));
}
}
