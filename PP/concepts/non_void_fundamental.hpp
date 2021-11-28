#pragma once
#include <PP/macros/simple_concept.hpp>
#include <PP/arithmetic.hpp>
#include <PP/fundamental_types.hpp>

namespace PP::concepts
{
template <typename T>
concept non_void_fundamental = arithmetic<T> || null<T>;
}

namespace PP
{
PP_CONCEPT_FUNCTOR1(non_void_fundamental);
}
