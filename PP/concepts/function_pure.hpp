#pragma once
#include "../negate.hpp"
#include "atomic/referencable.hpp"
#include "object.hpp"

namespace PP
{
PP_CIA is_function_pure = is_referencable && negate(is_object);

PP_CONCEPT1(function_pure)
}
