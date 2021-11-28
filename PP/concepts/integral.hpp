#pragma once
#include <PP/character.hpp>
#include <PP/fundamental_types.hpp>
#include <PP/integer.hpp>

namespace PP
{
namespace concepts
{
template <typename T>
concept integral = integer<T> || character<T> || bool_type<T>;
}

PP_CONCEPT_FUNCTOR1(integral);
}
