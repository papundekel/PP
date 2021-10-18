#pragma once
#include <iosfwd>
#include <string_view>

namespace PPtest
{
using test_function_type = void(std::ostream& out_key, std::ostream& out_run);

template <int I>
test_function_type test_function;

template <int I>
std::string_view test_function_name();
}
