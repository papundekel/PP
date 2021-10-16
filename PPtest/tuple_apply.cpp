#include <iostream>

#include "PP/containers/tuple.hpp"
#include "PP/tuple/apply.hpp"

namespace PPtest
{
void tuple_apply(std::ostream& out_key, std::ostream& out_run)
{
    out_key << "1 2 3";
    //
    PP::tuple::apply(
        [&out_run](int a, int b, int c) -> auto&
        {
            return out_run << a << ' ' << b << ' ' << c;
        },
        PP::tuple::make(1, 2, 3));
}
}
