#pragma once
#include "function_pure.hpp"
#include "object.hpp"

namespace PP::concepts
{
template <typename T>
concept referencable = function_pure<T> || object<T>;
}
