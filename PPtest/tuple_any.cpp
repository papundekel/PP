#include <iostream>

#include "PP/containers/tuple.hpp"
#include "PP/tuple/any.hpp"

namespace PPtest
{
void tuple_any(std::ostream& out_key, std::ostream& out_run)
{
    out_key << "1 2 true";
    //
    out_run << std::boolalpha
            << PP::tuple::any(
                   [&out_run](int x)
                   {
                       out_run << x << ' ';
                       return x % 2 == 0;
                   },
                   PP::tuple::make(1, 2, 4, 5));
}
}
