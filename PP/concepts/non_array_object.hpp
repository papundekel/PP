#pragma once
#include "atomic/non_array_object.hpp"

#include "non_void_fundamental.hpp"
#include "pointer.hpp"
#include "pointer_to_member.hpp"
#include "user_defined.hpp"

namespace PP
{
	namespace concepts
	{
		template <typename T>
		concept non_array_object = atomic::non_array_object<T> ||
			non_void_fundamental<T> ||
			pointer<T> ||
			pointer_to_member<T> ||
			user_defined<T>);
	}
}
