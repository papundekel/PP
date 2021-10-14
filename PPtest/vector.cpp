#include <iostream>

#include "PP/vector.hpp"

namespace PPtest
{
void vector()
{
    PP::vector<int> v;

    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    for (const auto& e : v)
        std::cout << e << ", ";
    std::cout << '\n';
}
}
