#pragma once
#include "compose.hpp"
#include "pack/fold.hpp"
#include "partial_c.hpp"

namespace PP
{
PP_CIA compose_many = partial_first_c(pack::fold)(value_true, compose);
}
