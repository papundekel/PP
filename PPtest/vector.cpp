#include <iostream>

#include "PP/vector.hpp"

namespace PPtest
{
void vector()
{
    PP::vector<int> v;

    for (int i = 0; i != 17; ++i)
        v.push_back(i);

    for (const auto& e : v)
        std::cout << e << ", ";
    std::cout << '\n';
}
}
