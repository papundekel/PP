#include "PP/call_reorder.hpp"

#include <iostream>

void test(std::ostream& out_key, std::ostream& out_run)
{
    out_key << "12";
    //
    int a = 0;
    int b = 0;

    auto x = PP::call_reorder(
        [](auto& x)
        {
            return [&x](auto& y)
            {
                x = 1;
                y = 2;
            };
        });
    auto y = x(PP::forward(b));
    y(a);

    out_run << a << b;
}
