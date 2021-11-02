#include "PPtest.hpp"

#include "PP/pack/fold.hpp"

#include <iostream>

namespace PPtest
{
template <>
std::string_view test_function_name<6>()
{
    return __FILE__;
}

template <>
void test_function<6>(std::ostream& out_key, std::ostream& out_run)
{
    out_key << "112";
    //
    int a = 3, b = 3, c = 3;

    auto f = [&out_run, &a, &b, &c](auto dir) -> decltype(auto)
    {
        return PP::pack::fold(
            dir,
            [&out_run](int& x, int& y) -> int&
            {
                x = 1;
                return y;
            },
            PP::forward_wrap(PP::placeholder, a))(b, c);
    };

    f(PP::value_true) = 2;
    out_run << a << b << c;
}
}
