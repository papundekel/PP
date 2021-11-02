#pragma once
#include "compose.hpp"
#include "pack/fold.hpp"
#include "partial_.hpp"

namespace PP
{
PP_CIA compose_many = partial_first(pack::fold, value_true, compose);
}
