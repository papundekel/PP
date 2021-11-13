#include "PPtest/counter.hpp"

#include "PP/combine_meta_c.hpp"

#include <iostream>

void test(std::ostream& out_key, std::ostream& out_run)
{
    out_key << "123,210";
    //
    int a, b, c;
    a = b = c = 0;

    auto x = PP::combine_meta_c(
        [](auto a, auto c)
        {
            a() = 1;
            c() = 3;
        });

    auto y = x(
        [&a](int& x) -> auto& {
            ++x;
            return a;
        },
        [&c](int& x) -> auto& {
            ++x;
            return c;
        });

    y(b);

    out_run << a << b << c << ",";

    PP::combine_meta_c([x = PPtest::counter(a)](auto&&) {})(
        [y = PPtest::counter(b)](auto&&) {})(PPtest::counter(c));

    out_run << a << b << c;
}
