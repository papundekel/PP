#pragma once
#include <PP/macros/simple_concept.hpp>
#include <PP/negate.hpp>
#include <PP/atomic/pointable.hpp>
#include <PP/reference.hpp>

namespace PP
{
PP_CIA is_function_cvref = !is_reference && !is_pointable;

PP_CONCEPT1(function_cvref)
}
