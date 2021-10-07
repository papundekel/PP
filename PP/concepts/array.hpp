#pragma once
#include "../get_type.hpp"
#include "../macros/simple_concept.hpp"
#include "bounded_array.hpp"
#include "unbounded_array.hpp"

namespace PP
{
namespace concepts
{
template <typename T>
concept array = bounded_array<T> || unbounded_array<T>;
}

PP_CONCEPT_FUNCTOR1(array);
}
