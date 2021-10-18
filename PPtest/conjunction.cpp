#include "PP/conjunction.hpp"
#include "PPtest.hpp"

#include <iostream>

namespace PPtest
{
namespace
{
bool is_even(int a)
{
    return a % 2 == 0;
}
bool is_positive(int a)
{
    return a > 0;
}
}
template<> std::string_view test_function_name<2>() { return __FILE__; }

template<>
void test_function<2>(std::ostream& out_key, std::ostream& out_run)
{
    out_key << "false false false true false true";
    //
    auto combined = PP::conjunction(is_even, is_positive);

    out_run << std::boolalpha << combined(-1) << ' ' << combined(0) << ' '
            << combined(1) << ' ' << combined(2) << ' ' << combined(3) << ' '
            << combined(4);
}
}
