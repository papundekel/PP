#pragma once
#include "non_array_object.hpp"
#include "reference.hpp"
#include "void.hpp"

namespace PP::concepts
{
template <typename T>
concept returnable = reference<T> || void_type<T> || non_array_object<T>;
}
