#pragma once
#include <PP/negate.hpp>
#include <PP/atomic/referencable.hpp>
#include <PP/object.hpp>

namespace PP
{
PP_CIA is_function_pure = is_referencable && negate(is_object);

PP_CONCEPT1(function_pure)
}
