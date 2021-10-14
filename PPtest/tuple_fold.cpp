#include <iostream>

#include "PP/containers/tuple.hpp"
#include "PP/tuple/fold.hpp"

namespace PPtest
{
void tuple_fold()
{
    std::cout << PP::tuple::fold_init_pack(
                     PP::value_true,
                     [](int x, int y)
                     {
                         return x + y;
                     },
                     []{ return 0; },
                     1, 2, 3, 4)
              << ' '
              << PP::tuple::fold_init(
                     PP::value_true,
                     [](int x, int y)
                     {
                         return x + y;
                     },
                     []{ return 0; },
                     PP::tuple::make(1, 2, 3, 4))
              << ' '
              << PP::tuple::fold(
                     PP::value_true,
                     [](int x, int y)
                     {
                         return x + y;
                     },
                     0,
                     PP::tuple::make(1, 2, 3, 4))
              << '\n';
}
}
