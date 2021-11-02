#pragma once
#include "../compose.hpp"
#include "../operators.hpp"
#include "../partial.hpp"
#include "../tuple.hpp"
#include "apply.hpp"
#include "fold.hpp"

namespace PP::tuple
{
PP_CIA disjunction = foldl * or_ * false;
}
