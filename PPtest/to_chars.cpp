#include <cstdlib>
#include <ctime>
#include <iostream>

#include "PP/to_chars.hpp"

namespace PPtest
{
void to_chars(std::ostream& out_key, std::ostream& out_run)
{
    std::srand(std::time(nullptr));
    int a = std::rand();

    out_key << a;
    //
    char buff[32];
    buff[31] = 0;

    out_run << PP::to_chars(
        PP::view::pair(std::begin(buff), std::end(buff) - 1),
        a);
}
}
