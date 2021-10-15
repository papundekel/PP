#include <iostream>

#include "PP/view/unbounded.hpp"
#include "PP/view/zip.hpp"

namespace PPtest
{
void zip_unbounded()
{
    int a[] = {0, 1, 2, 3};
    double b[4];

    auto v = PP::view::zip_pack(PP::view::begin_(a) ^ PP::view::unbounded, b);

    for (auto [x, y] : v)
        std::cout << x << ", ";
    std::cout << '\n';
}
}
