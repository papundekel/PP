#pragma once
#include "apply_partially_first.hpp"
#include "compose.hpp"
#include "pack/fold.hpp"

namespace PP
{
PP_CIA compose_many = apply_partially_first(pack::fold, value_true, compose);
}
