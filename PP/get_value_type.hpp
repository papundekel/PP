#pragma once
#include "get_type.hpp"
#include "get_value.hpp"

namespace PP
{
template <typename T>
using get_value_type = decltype(get_value<T>());
}
