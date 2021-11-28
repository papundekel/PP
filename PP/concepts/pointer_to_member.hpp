#pragma once
#include <PP/compose.hpp>
#include <PP/get_type.hpp>
#include <PP/overloaded.hpp>
#include <PP/remove_cv.hpp>

namespace PP
{
PP_CIA is_pointer_to_member =
    compose(overloaded(
                []<typename T, typename Class>(type_t<T Class::*>)
                {
                    return true;
                },
                [](auto&&)
                {
                    return false;
                }),
            remove_cv);

PP_CONCEPT1(pointer_to_member)
}
