#include <iostream>

#include "PP/conjunction.hpp"

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
void conjunction(std::ostream& out_key, std::ostream& out_run)
{
    out_key << "false false false true false true";
    //
    auto combined = PP::conjunction(is_even, is_positive);

    out_run << std::boolalpha << combined(-1) << ' ' << combined(0) << ' '
            << combined(1) << ' ' << combined(2) << ' ' << combined(3) << ' '
            << combined(4);
}
}
