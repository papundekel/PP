#pragma once
#include "atomic/reference.hpp"
#include "lvalue_reference.hpp"
#include "rvalue_reference.hpp"

namespace PP::concepts
{
template <typename T>
concept reference =
	is_reference(PP::type<T>) || lvalue_reference<T> || rvalue_reference<T>;
}
