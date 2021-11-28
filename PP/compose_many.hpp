#pragma once
#include <PP/compose.hpp>
#include <PP/pack/fold.hpp>
#include <PP/partial_first_c.hpp>

namespace PP
{
PP_CIA compose_many = partial_first_c(pack::fold)(value_true, compose);
}
