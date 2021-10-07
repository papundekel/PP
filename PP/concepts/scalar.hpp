#pragma once
#include "enum.hpp"
#include "non_void_fundamental.hpp"
#include "pointer.hpp"
#include "pointer_to_member.hpp"

namespace PP
{
namespace concepts
{
template <typename T>
concept scalar = non_void_fundamental<T> || pointer<T> ||
    pointer_to_member<T> || enum_type<T>;
}

PP_CONCEPT_FUNCTOR1(scalar);
}
