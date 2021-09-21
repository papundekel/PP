#pragma once
#include "compose.hpp"
#include "get_type.hpp"

namespace PP
{
PP_CIA add_const = functor(
                       []<typename T>(type_t<T>)
                       {
                           return type<const T>;
                       }) |
                   to_type_t;
}
