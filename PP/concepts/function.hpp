#pragma once
#include <PP/get_type.hpp>
#include <PP/function_cvref.hpp>
#include <PP/function_pure.hpp>

namespace PP
{
namespace concepts
{
template <typename T>
concept function = function_pure<T> || function_cvref<T>;
}

PP_CONCEPT_FUNCTOR1(function);
}
