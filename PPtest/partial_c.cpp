#include "PPtest.hpp"

#include "PP/partial_.hpp"

#include <iostream>

namespace PPtest
{
template <>
std::string_view test_function_name<0>()
{
    return __FILE__;
}

template <>
void test_function<0>(std::ostream& out_key, std::ostream& out_run)
{
    out_key << "123123123";
    //
    auto f = [&out_run](int a, int b, int c)
    {
        out_run << a << b << c;
    };
    PP::partial_c(f)(1)(3)(2);
    PP::partial_first_c(f)(1)(2, 3);
    PP::partial_last_c(f)(3)(1, 2);
}
}
