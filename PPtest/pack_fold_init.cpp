#include "PPtest.hpp"

#include "PP/pack/fold_init.hpp"

#include <iostream>

namespace PPtest
{
template <>
std::string_view test_function_name<3>()
{
    return __FILE__;
}

template <>
void test_function<3>(std::ostream& out_key, std::ostream& out_run)
{
    out_key << "0-1-3-6-10-15-5-4-3-2-1-15/112";
    //
    auto f = [&out_run](auto dir)
    {
        return PP::pack::fold_init(
                   dir,
                   [&out_run](uncopiable<int> a, uncopiable<int> b)
                   {
                       out_run << a.val << "-";
                       return uncopiable(a.val + b.val);
                   },
                   []
                   {
                       return 0;
                   })(1, 2, 3, 4, 5)
            .val;
    };
    out_run << f(PP::value_true) << "-" << f(PP::value_false) << "/";

    int a = 3, b = 3, c = 3;

    auto g = [&out_run, &a, &b, &c](auto dir) -> decltype(auto)
    {
        return PP::pack::fold_init(
            dir,
            [&out_run](int& x, int& y) -> int&
            {
                x = 1;
                return y;
            },
            [&a]() -> int&
            {
                return a;
            })(b, c);
    };

    g(PP::value_true) = 2;
    out_run << a << b << c;
}
}
