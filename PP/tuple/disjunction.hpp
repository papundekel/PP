#pragma once
#include <PP/compose.hpp>
#include <PP/operators.hpp>
#include <PP/partial.hpp>
#include <PP/tuple/concept.hpp>
#include <PP/tuple/apply.hpp>
#include <PP/tuple/fold.hpp>

namespace PP::tuple
{
PP_CIA disjunction = foldl * or_ * false;
}
