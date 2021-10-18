#include "PPtest.hpp"

#include "PP/containers/tuple.hpp"
#include "PP/tuple/concat.hpp"

#include <iostream>

namespace PPtest
{
template<> std::string_view test_function_name<8>() { return __FILE__; }

template<>
void test_function<8>(std::ostream& out_key, std::ostream& out_run)
{
    out_key << "5 6";
    //
    int a = 1;
    int b = 2;

    auto concatenated =
        PP::tuple::concat(PP::tuple::forward(a), PP::tuple::forward(b));

    concatenated[PP::value_0] = 5;
    concatenated[PP::value_1] = 6;

    out_run << a << ' ' << b;
}
}
