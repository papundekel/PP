#include <iostream>

#include "PP/containers/tuple.hpp"
#include "PP/tuple/apply.hpp"

namespace PPtest
{
void tuple_apply()
{
    PP::tuple::apply(
        [](int a, int b, int c) -> auto&
        {
            return std::cout << a << ' ' << b << ' ' << c;
        },
        PP::tuple::make(1, 2, 3))
        << '\n';
}
}
