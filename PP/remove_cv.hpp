#pragma once
#include "compose.hpp"
#include "remove_const.hpp"
#include "remove_volatile.hpp"

namespace PP
{
PP_CIA remove_cv = compose(remove_volatile, remove_const);
}
