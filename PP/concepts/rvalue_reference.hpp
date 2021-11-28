#pragma once
#include <PP/negate.hpp>
#include <PP/atomic/reference.hpp>
#include <PP/lvalue_reference.hpp>

namespace PP
{
PP_CIA is_rvalue_reference = is_reference && negate(is_lvalue_reference);

PP_CONCEPT1(rvalue_reference)
}
