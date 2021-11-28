#pragma once
#include <PP/get_type.hpp>
#include <PP/get_value.hpp>

namespace PP
{
template <typename T>
using get_value_type = decltype(get_value<T>());
}
