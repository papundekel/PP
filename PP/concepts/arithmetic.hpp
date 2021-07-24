#pragma once
#include "floating_point.hpp"
#include "integral.hpp"

namespace PP::concepts
{
template <typename T>
concept arithmetic = integral<T> || floating_point<T>;
}
