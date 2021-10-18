#include "PPtest.hpp"

#include "PP/containers/tuple.hpp"
#include "PP/tuple/any.hpp"

#include <iostream>

namespace PPtest
{
template<> std::string_view test_function_name<6>() { return __FILE__; }

template<>
void test_function<6>(std::ostream& out_key, std::ostream& out_run)
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
