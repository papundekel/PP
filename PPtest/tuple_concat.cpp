#include <iostream>

#include "PP/containers/tuple.hpp"
#include "PP/tuple/concat.hpp"

namespace PPtest
{
void tuple_concat(std::ostream& out_key, std::ostream& out_run)
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
