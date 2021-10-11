#pragma once
#include "compose.hpp"
#include "get_type.hpp"

namespace PP::functors
{
PP_CIA add_volatile = []<typename T>(type_t<T>)
{
    return type<volatile T>;
} | to_type_t;
}

namespace PP
{
using functors::add_volatile;
}
