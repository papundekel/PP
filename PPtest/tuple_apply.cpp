#include "PPtest.hpp"

#include "PP/containers/tuple.hpp"
#include "PP/tuple/apply.hpp"

#include <iostream>

namespace PPtest
{
template<> std::string_view test_function_name<7>() { return __FILE__; }

template<>
void test_function<7>(std::ostream& out_key, std::ostream& out_run)
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
