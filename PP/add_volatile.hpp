#pragma once
#include "compose.hpp"
#include "to_type_t.hpp"

namespace PP
{
PP_CIA add_volatile = compose(
    []<typename T>(type_t<T>)
    {
        return type<volatile T>;
    },
    to_type_t);
}
