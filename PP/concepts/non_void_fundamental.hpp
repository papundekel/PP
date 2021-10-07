#pragma once
#include "../macros/simple_concept.hpp"
#include "arithmetic.hpp"
#include "fundamental_types.hpp"

namespace PP
{
namespace concepts
{
template <typename T>
concept non_void_fundamental = arithmetic<T> || null<T>;
}

PP_CONCEPT_FUNCTOR1(non_void_fundamental);
}
