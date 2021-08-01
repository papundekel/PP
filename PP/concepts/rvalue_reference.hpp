#pragma once
#include "../negate.hpp"
#include "atomic/reference.hpp"
#include "lvalue_reference.hpp"

namespace PP
{
PP_CIA is_rvalue_reference = is_reference && !is_lvalue_reference;

PP_CONCEPT1(rvalue_reference)
}
