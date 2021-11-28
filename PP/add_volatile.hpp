#pragma once
#include <PP/compose.hpp>
#include <PP/to_type_t.hpp>

namespace PP
{
PP_CIA add_volatile = compose(
    []<typename T>(type_t<T>)
    {
        return type<volatile T>;
    },
    to_type_t);
}
