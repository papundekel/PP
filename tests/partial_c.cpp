#include "PPtest/counter.hpp"

#include "PP/partial_c.hpp"

#include <iostream>

void test(std::ostream& out_key, std::ostream& out_run)
{
    out_key << "123,210,";
    //
    int a = 0;
    int b = 0;
    int c = 0;

    auto print = [&out_run, &a, &b, &c]()
    {
        out_run << a << b << c << ",";
    };

    auto x = PP::partial_c(
        [&out_run](int& a, int& b, int& c)
        {
            a = 1;
            b = 2;
            c = 3;
        });
    auto y = x(PP::forward(PP::value_2, a));
    auto z = y(PP::forward(c));

    z(b);

    print();

    PP::partial_c([&out_run](auto&& a, auto&& b, auto&& c) {})(
        PPtest::counter{a})(PPtest::counter{b})(PPtest::counter{c});

    print();
}
