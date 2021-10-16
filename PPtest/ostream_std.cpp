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
void ostream_std(std::ostream& out_key, std::ostream& out_run)
{
    f(out_key);
    //
    PP::ostream_std pp_out(out_run);
    f(pp_out);
}
}
