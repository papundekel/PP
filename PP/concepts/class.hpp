#pragma once
#include <PP/get_type.hpp>
#include <PP/concepts/atomic/class.hpp>
#include <PP/concepts/non_union_class.hpp>
#include <PP/concepts/union.hpp>

namespace PP::concepts
{
template <typename T>
concept class_type =
    is_class(PP::type<T>) || non_union_class<T> || union_type<T>;
}
