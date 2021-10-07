#pragma once
#include "../functor.hpp"
#include "../get_type.hpp"
#include "function_cvref.hpp"
#include "function_pure.hpp"

namespace PP
{
namespace concepts
{
template <typename T>
concept function = function_pure<T> || function_cvref<T>;
}

PP_CONCEPT_FUNCTOR1(function);
}
