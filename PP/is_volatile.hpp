#pragma once
#include "compose.hpp"
#include "get_value.hpp"
#include "get_volatile.hpp"

namespace PP
{
PP_CIA is_volatile = compose(compose(cv_is_volatile, get_value), get_volatile);
}
