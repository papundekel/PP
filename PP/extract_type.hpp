#pragma once
#include <PP/get_type.hpp>
#include <PP/type_t.hpp>

namespace PP
{
template <typename T>
using extract_type = type_t<get_type<T>>;
}
