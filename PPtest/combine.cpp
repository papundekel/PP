#include <iostream>

#include "PP/combine.hpp"

namespace PPtest
{
void combine()
{
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

    std::cout << std::boolalpha << combined(-1) << ' ' << combined(0) << ' '
              << combined(1) << ' ' << combined(2) << ' ' << combined(3) << ' '
              << combined(4) << '\n';
}
}
