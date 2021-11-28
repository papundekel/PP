#pragma once
#include <PP/non_array_object.hpp>
#include <PP/reference.hpp>
#include <PP/void.hpp>

namespace PP::concepts
{
template <typename T>
concept returnable = reference<T> || void_type<T> || non_array_object<T>;
}
