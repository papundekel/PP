#include <iostream>

#include "PP/to_chars.hpp"

namespace PPtest
{
void to_chars()
{
    char buff[100];
    buff[99] = 0;

    int a = 25;

    auto b = PP::to_chars(PP::view::pair(buff + 0, buff + 99), a);

    std::cout << "should be: " << a << ", is: " << b << '\n';
}
}
