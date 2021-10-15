#include "PP/ostream.hpp"

#include <iostream>

namespace PPtest
{
namespace
{
    void f(auto& out)
    {
        out << "cauko mnauko" << ' ' << 25;
    }
}
void cout()
{
    std::cout << "should be: ";
    f(std::cout);    
    std::cout << '\n'
              << "       is: ";
    f(PP::cout);  
    std::cout << '\n';
}
}
