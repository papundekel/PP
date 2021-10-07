#pragma once
#include "../conjunction.hpp"
#include "../get_type.hpp"
#include "../negate.hpp"
#include "atomic/class.hpp"
#include "union.hpp"

namespace PP
{
PP_CIA is_non_union_class = is_class && !is_union;

PP_CONCEPT1(non_union_class)
}
