#include "PPtest.hpp"

#include "PP/ostream_std.hpp"

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
template<> std::string_view test_function_name<4>() { return __FILE__; }

template<>
void test_function<4>(std::ostream& out_key, std::ostream& out_run)
{
    f(out_key);
    //
    PP::ostream_std pp_out(out_run);
    f(pp_out);
}
}
