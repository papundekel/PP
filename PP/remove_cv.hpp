#pragma once
#include <PP/compose.hpp>
#include <PP/remove_const.hpp>
#include <PP/remove_volatile.hpp>

namespace PP
{
PP_CIA remove_cv = compose(remove_volatile, remove_const);
}
