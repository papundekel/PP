#pragma once
#include <PP/compose.hpp>
#include <PP/operators.hpp>
#include <PP/partial_.hpp>

namespace PP
{
PP_CIA negate = compose * neg;
}
