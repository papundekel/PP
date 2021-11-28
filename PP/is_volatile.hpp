#pragma once
#include <PP/compose.hpp>
#include <PP/get_value.hpp>
#include <PP/get_volatile.hpp>

namespace PP
{
PP_CIA is_volatile = compose_many(cv_is_volatile, get_value, get_volatile);
}
