#pragma once
#include <PP/floating_point.hpp>
#include <PP/integral.hpp>

namespace PP::concepts
{
template <typename T>
concept arithmetic = integral<T> || floating_point<T>;
}
