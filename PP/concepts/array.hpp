#pragma once
#include "../get_type.hpp"
#include "../macros/simple_concept.hpp"
#include "bounded_array.hpp"
#include "unbounded_array.hpp"

namespace PP::concepts
{
template <typename T>
concept array = bounded_array<T> || unbounded_array<T>;
}

namespace PP
{
namespace functors
{
PP_CONCEPT_FUNCTOR1(array);
}
PP_FUNCTOR(is_array)
}
