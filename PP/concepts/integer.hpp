#pragma once
#include <PP/concepts/signed_integer.hpp>
#include <PP/concepts/unsigned_integer.hpp>

namespace PP::concepts
{
template <typename T>
concept integer = signed_integer<T> || unsigned_integer<T>;
}
