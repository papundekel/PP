#pragma once
#include "compose.hpp"
#include "get_const.hpp"
#include "get_value.hpp"

namespace PP
{
PP_CIA is_const = compose_many(cv_is_const, get_value, get_const);
}
