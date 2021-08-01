#pragma once
#include "../functor.hpp"
#include "../get_type.hpp"
#include "complete_object.hpp"
#include "unbounded_array.hpp"

namespace PP::concepts
{
template <typename T>
concept object = complete_object<T> || unbounded_array<T>;
}

namespace PP
{
PP_CONCEPT_FUNCTOR1(object);
}
