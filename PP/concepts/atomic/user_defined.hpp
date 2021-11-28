#pragma once
#include <PP/negate.hpp>
#include <PP/non_void_fundamental.hpp>
#include <PP/pointer.hpp>
#include <PP/pointer_to_member.hpp>
#include <PP/non_array_object.hpp>

namespace PP
{
PP_CIA is_user_defined = is_non_array_object &&
                         negate(is_non_void_fundamental) &&
                         negate(is_pointer) && negate(is_pointer_to_member);
}
