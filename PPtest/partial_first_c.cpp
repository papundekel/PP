#include "PPtest.hpp"

#include "PP/partial_c.hpp"

#include <iostream>

namespace PPtest
{
template <>
std::string_view test_function_name<1>()
{
    return __FILE__;
}

template <>
void test_function<1>(std::ostream& out_key, std::ostream& out_run)
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

    PP::partial_first_c([&out_run](auto&& a, auto&& b) {})(counter{a})(
        counter{b});

    print();
}
}
