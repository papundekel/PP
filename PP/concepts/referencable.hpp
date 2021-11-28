#pragma once
#include <PP/function_pure.hpp>
#include <PP/object.hpp>

namespace PP::concepts
{
template <typename T>
concept referencable = function_pure<T> || object<T>;
}
