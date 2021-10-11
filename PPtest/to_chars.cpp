#include <iostream>

#include "PP/to_chars.hpp"

namespace PPtest
{
void to_chars()
{
    char buff[100];

    *PP::to_chars(buff, 25) = 0;

    std::cout << buff << '\n';
}
}
