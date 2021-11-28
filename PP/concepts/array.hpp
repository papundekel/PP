#pragma once
#include <PP/get_type.hpp>
#include <PP/macros/simple_concept.hpp>
#include <PP/concepts/bounded_array.hpp>
#include <PP/concepts/unbounded_array.hpp>

namespace PP::concepts
{
template <typename T>
concept array = bounded_array<T> || unbounded_array<T>;
}

namespace PP
{
PP_CONCEPT_FUNCTOR1(array);
}
