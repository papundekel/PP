#include "PPtest.hpp"

#include "PP/view/unbounded.hpp"
#include "PP/view/zip.hpp"

#include <iostream>

namespace PPtest
{
template<> std::string_view test_function_name<12>() { return __FILE__; }

template<>
void test_function<12>(std::ostream& out_key, std::ostream& out_run)
{
    int a[] = {0, 1, 2, 3};

    for (auto x : a)
        out_key << x << ", ";
    //
    double b[4];

    auto v = PP::view::zip_pack(PP::view::begin_(a) ^ PP::view::unbounded, b);

    for (auto [x, y] : v)
        out_run << x << ", ";
}
}
