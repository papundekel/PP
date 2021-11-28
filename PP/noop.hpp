#pragma once
#include <PP/macros/CIA.hpp>

namespace PP
{
PP_CIA noop = [](auto&&...) {};
}
