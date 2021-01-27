#pragma once
#include "atomic/complete_object.hpp"
#include "bounded_array.hpp"
#include "non_array_object.hpp"

namespace PP::concepts
{
	template <typename T>
	concept complete_object = is_complete_object(PP::type<T>) ||
		bounded_array<T> ||
		non_array_object<T>;
}
