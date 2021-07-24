#pragma once
#include "fundamental_types.hpp"

namespace PP
{
namespace concepts
{
template <typename T>
concept signed_integer =
	signed_short<T> || signed_int<T> || signed_long<T> || signed_long_long<T>;
}
}
