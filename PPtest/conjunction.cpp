#include "PP/conjunction.hpp"
#include "PPtest.hpp"

#include <iostream>

namespace PPtest
{
template <typename T>
bool operator&&(uncopiable<T> a, uncopiable<T> b)
{
    return a.val && b.val;
}
template <typename T>
bool operator&&(bool a, uncopiable<T> b)
{
    return a && b.val;
}

template <>
std::string_view test_function_name<3>()
{
    return __FILE__;
}

template <>
void test_function<3>(std::ostream& out_key, std::ostream& out_run)
{
    out_key << "0 0 0 1 0 - 0 0 0 0 1 - ";

    auto l = lambda(
        [](int div, auto&& a)
        {
            return uncopiable(a.val % div == 0);
        },
        2);

    auto combined = PP::conjunction(
        PP_FW(l),
        [](auto&& a)
        {
            return uncopiable(a.val % 3 == 0);
        },
        [](auto&& a)
        {
            return uncopiable(a.val > 0);
        });

    auto g = [&combined](int a)
    {
        return combined(uncopiable(a));
    };

    auto f = [&g, &combined, &out_run]()
    {
        out_run << std::noboolalpha << g(0) << ' ' << g(4) << ' ' << g(9) << ' '
                << g(6) << ' ' << g(15) << " - ";
    };

    f();
    l.val = 5;
    f();
}
}
