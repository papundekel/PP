#include "PPtest/counter.hpp"

#include "PP/partial_first_c.hpp"

void test(std::ostream& out_key, std::ostream& out_run)
{
    out_key << "210,110,010,";
    //
    int a, b, c;
    a = b = c = 0;

    auto print = [&]()
    {
        out_run << a << b << c << ",";
    };

    PP::partial_first_c([x = PPtest::counter(a)](auto&&, auto&&) {})(
        PPtest::counter(b))(PPtest::counter(c));

    print();

    auto f = [x = PPtest::counter(a)](auto&&, auto&&) {};

    PP::partial_first_c(PP::forward(f))(PPtest::counter(b))(PPtest::counter(c));

    print();

    auto g = [x = PPtest::counter(a)](auto&&, auto&&) {};

    PP::partial_first_c(PP::forward(PP::value_2, g))(PPtest::counter(b))(
        PPtest::counter(c));

    print();
}
