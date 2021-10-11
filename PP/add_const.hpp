#pragma once
#include "compose.hpp"
#include "get_type.hpp"

namespace PP
{
namespace functors
{
PP_CIA add_const = []<typename T>(type_t<T>)
{
    return type<const T>;
} | to_type_t;
}
PP_FUNCTOR(add_const)
}
