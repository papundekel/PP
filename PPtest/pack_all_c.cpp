#include "PPtest.hpp"

#include "PP/pack/all_c.hpp"

#include <iostream>

namespace PPtest
{
template <>
std::string_view test_function_name<1>()
{
    return __FILE__;
}

template <>
void test_function<1>(std::ostream& out_key, std::ostream& out_run)
{
    out_key << "10";
    //
    out_run << std::noboolalpha
            << PP::pack::all_c(
                   [](int x)
                   {
                       return x > 0;
                   })(1, 2, 3)
            << PP::pack::all_c(
                   [](int x)
                   {
                       return x > 0;
                   })(1, 0, 3);
}
}
