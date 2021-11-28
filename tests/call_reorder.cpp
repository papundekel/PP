#include "PP/call_reorder.hpp"

void test(std::ostream& out_key, std::ostream& out_run)
{
    out_key << "12";
    //
    int a, b;
    a = b = 0;

    PP::call_reorder(
        [](auto&& x)
        {
            return [PP_FL(x)](auto& y)
            {
                PP::backward(x) = 1;
                y = 2;
            };
        })(PP::forward(b))(a);

    out_run << a << b;
}
