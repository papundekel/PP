#pragma once
#include <PP/get_type.hpp>
#include <PP/class.hpp>
#include <PP/enum.hpp>

namespace PP
{
namespace concepts
{
template <typename T>
concept user_defined =
    is_user_defined(PP::type<T>) || class_type<T> || enum_type<T>;
}
}
