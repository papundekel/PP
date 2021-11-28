#pragma once
#include <PP/atomic/non_array_object.hpp>

#include <PP/non_void_fundamental.hpp>
#include <PP/pointer.hpp>
#include <PP/pointer_to_member.hpp>
#include <PP/user_defined.hpp>

namespace PP::concepts
{
template <typename T>
concept non_array_object =
    is_non_array_object(PP::type<T>) || non_void_fundamental<T> || pointer<T> ||
    pointer_to_member<T> || user_defined<T>;
}
