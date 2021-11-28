#pragma once
#include <PP/atomic/pointable.hpp>
#include <PP/fundamental_types.hpp>
#include <PP/referencable.hpp>

namespace PP
{
namespace concepts
{
template <typename T>
concept pointable =
    is_pointable(PP::type<T>) || referencable<T> || void_type<T>;
}
}
