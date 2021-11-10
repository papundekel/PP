#include "PPtest/uncopiable.hpp"

#include "PP/pack/map_c.hpp"

#include <iostream>

void test(std::ostream& out_key, std::ostream& out_run)
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
            return PPtest::uncopiable(x * 2);
        })(1, 2, 3);
}
