#include "PP/combine.hpp"
#include "PPtest.hpp"

#include <iostream>

namespace PPtest
{
template<> std::string_view test_function_name<1>() { return __FILE__; }

template<>
void test_function<1>(std::ostream& out_key, std::ostream& out_run)
{
    out_key << "false false false true false true";
    //
    auto combined = PP::combine(
        [](bool a, bool b)
        {
            return a && b;
        },
        [](int a)
        {
            return a % 2 == 0;
        },
        [](int a)
        {
            return a > 0;
        });

    out_run << std::boolalpha << combined(-1) << ' ' << combined(0) << ' '
            << combined(1) << ' ' << combined(2) << ' ' << combined(3) << ' '
            << combined(4);
}
}
