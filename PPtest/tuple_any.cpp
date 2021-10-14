#include <iostream>

#include "PP/tuple/any.hpp"
#include "PP/containers/tuple.hpp"

namespace PPtest
{
void tuple_any()
{
    std::cout << std::boolalpha
              << PP::tuple::any(
                     [](int x)
                     {
                         std::cout << x << ' ';
                         return x % 2 == 0;
                     },
                     PP::tuple::make(1, 2, 4, 5))
              << '\n';
}
}
