#include <iostream>

#include "PP/to_chars.hpp"

namespace PPtest
{
void to_chars()
{
    char buff[100];

    int a = 25;

    *PP::to_chars(buff, a) = 0;

    std::cout << "should be: " << a << ", is: " << buff << '\n';
}
}
