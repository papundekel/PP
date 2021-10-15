#pragma once
#include "../get_type.hpp"
#include "class.hpp"
#include "enum.hpp"

namespace PP
{
namespace concepts
{
template <typename T>
concept user_defined =
    is_user_defined(PP::type<T>) || class_type<T> || enum_type<T>;
}
}
