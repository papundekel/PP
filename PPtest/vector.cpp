#include <iostream>

#include "PP/vector.hpp"

namespace PPtest
{
void vector(std::ostream& out_key, std::ostream& out_run)
{
    out_key << "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, ";
    //
    PP::vector<int> v;

    for (int i = 0; i != 17; ++i)
        v.push_back(i);

    for (const auto& e : v)
        out_run << e << ", ";
}
}
