#pragma once
#include "../functor.hpp"
#include "../negate.hpp"
#include "atomic/user_defined.hpp"
#include "class.hpp"

namespace PP
{
PP_CIA is_enum = is_user_defined && !is_class;

PP_CONCEPT(enum_type, enum)
}
