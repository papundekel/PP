#pragma once
#include "compose.hpp"
#include "get_type.hpp"

namespace PP
{
PP_CIA add_volatile = compose(
    []<typename T>(type_t<T>)
    {
        return type<volatile T>;
    },
    to_type_t);
}
