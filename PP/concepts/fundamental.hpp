#pragma once
#include <PP/fundamental_types.hpp>
#include <PP/non_void_fundamental.hpp>

namespace PP::concepts
{
template <typename T>
concept fundamental = non_void_fundamental<T> || void_type<T>;
}
