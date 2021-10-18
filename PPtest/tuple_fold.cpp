#include "PPtest.hpp"

#include "PP/containers/tuple.hpp"
#include "PP/tuple/fold.hpp"

#include <iostream>

namespace PPtest
{
template<> std::string_view test_function_name<9>() { return __FILE__; }

template<>
void test_function<9>(std::ostream& out_key, std::ostream& out_run)
{
    out_key << "10 10 10";
    //
    out_run << PP::pack::fold_init(
                   PP::value_true,
                   [](int x, int y)
                   {
                       return x + y;
                   },
                   []
                   {
                       return 0;
                   },
                   1,
                   2,
                   3,
                   4)
            << ' '
            << PP::tuple::fold_init(
                   PP::value_true,
                   [](int x, int y)
                   {
                       return x + y;
                   },
                   []
                   {
                       return 0;
                   },
                   PP::tuple::make(1, 2, 3, 4))
            << ' '
            << PP::tuple::fold(
                   PP::value_true,
                   [](int x, int y)
                   {
                       return x + y;
                   },
                   0,
                   PP::tuple::make(1, 2, 3, 4));
}
}
