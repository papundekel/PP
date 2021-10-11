#pragma once
#include "../macros/simple_concept.hpp"
#include "arithmetic.hpp"
#include "fundamental_types.hpp"

namespace PP::concepts
{
template <typename T>
concept non_void_fundamental = arithmetic<T> || null<T>;
}

namespace PP
{
namespace functors
{
PP_CONCEPT_FUNCTOR1(non_void_fundamental);
}
PP_FUNCTOR(is_non_void_fundamental)
}
