#pragma once
#include <PP/conjunction.hpp>
#include <PP/concepts/atomic/complete_object.hpp>
#include <PP/concepts/atomic/returnable.hpp>

namespace PP
{
PP_CIA is_non_array_object = is_complete_object && is_returnable;
}
