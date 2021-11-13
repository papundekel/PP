#include "PPtest/counter.hpp"

#include "PP/partial_c.hpp"

#include <iostream>

void test(std::ostream& out_key, std::ostream& out_run)
{
    out_key << "3210,";
    //
    int a, b, c, d;
    a = b = c = d = 0;

    auto print = [&]()
    {
        out_run << a << b << c << d << ",";
    };

    PP::partial_c([x = PPtest::counter{a}](auto&&, auto&&, auto&&) {})(
        PPtest::counter{b})(PPtest::counter{c})(PPtest::counter{d});

    print();
}
