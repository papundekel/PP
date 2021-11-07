#include "PPtest.hpp"

#include "PP/call_reorder.hpp"

#include <iostream>

namespace PPtest
{
template <>
std::string_view test_function_name<5>()
{
    return __FILE__;
}

template <>
void test_function<5>(std::ostream& out_key, std::ostream& out_run)
{
    out_key << "12";
    //
    int a = 0;
    int b = 0;

    auto x = PP::call_reorder([](auto& x){  return [&x](auto& y){ x = 1; y = 2; }; });
    auto y = x(PP::forward_wrap(PP::value_0, b));
    y(a);
    
    out_run << a << b;
}
}
