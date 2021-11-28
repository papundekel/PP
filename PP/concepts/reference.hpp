#pragma once
#include <PP/atomic/reference.hpp>
#include <PP/lvalue_reference.hpp>
#include <PP/rvalue_reference.hpp>

namespace PP::concepts
{
template <typename T>
concept reference =
    is_reference(PP::type<T>) || lvalue_reference<T> || rvalue_reference<T>;
}
