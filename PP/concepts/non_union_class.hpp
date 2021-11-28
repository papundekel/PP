#pragma once
#include <PP/conjunction.hpp>
#include <PP/get_type.hpp>
#include <PP/negate.hpp>
#include <PP/concepts/atomic/class.hpp>
#include <PP/concepts/union.hpp>

namespace PP
{
PP_CIA is_non_union_class = is_class && negate(is_union);

PP_CONCEPT1(non_union_class)
}
