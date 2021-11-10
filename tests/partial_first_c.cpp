#include "PPtest/counter.hpp"

#include "PP/partial_c.hpp"

#include <iostream>

void test(std::ostream& out_key, std::ostream& out_run)
{
    out_key << "12,10,";
    //
    int a = 0;
    int b = 0;

    auto print = [&out_run, &a, &b]()
    {
        out_run << a << b << ",";
    };

    auto x = PP::partial_first_c(
        [](int& a, int& b)
        {
            a = 1;
            b = 2;
        });
    auto y = x(PP::forward(a));

    y(b);

    print();

    PP::partial_first_c([&out_run](auto&& a, auto&& b) {})(PPtest::counter{a})(
        PPtest::counter{b});

    print();
}
