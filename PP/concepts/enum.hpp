#pragma once
#include <PP/negate.hpp>
#include <PP/atomic/user_defined.hpp>
#include <PP/class.hpp>

namespace PP
{
PP_CIA is_enum = is_user_defined && negate(is_class);

PP_CONCEPT(enum_type, enum)
}
