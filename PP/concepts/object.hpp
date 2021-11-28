#pragma once
#include <PP/get_type.hpp>
#include <PP/complete_object.hpp>
#include <PP/concepts/unbounded_array.hpp>

namespace PP::concepts
{
template <typename T>
concept object = complete_object<T> || unbounded_array<T>;
}

namespace PP
{
PP_CONCEPT_FUNCTOR1(object);
}
