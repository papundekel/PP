#include "PPtest.hpp"

#include "PP/pack/map_c.hpp"

#include <iostream>

namespace PPtest
{
template <>
std::string_view test_function_name<4>()
{
    return __FILE__;
}

template <>
void test_function<4>(std::ostream& out_key, std::ostream& out_run)
{
    out_key << "12";
    //
    out_run << PP::pack::map_c(
        [](auto... a)
        {
            return (0 + ... + a.val);
        },
        [](int x)
        {
            return uncopiable(x * 2);
        })(1, 2, 3);
}
}
