#pragma once
#include "functor.hpp"

namespace PP
{
PP_CIA noop = [](auto&&...)
{
};
}
