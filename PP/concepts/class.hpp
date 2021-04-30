#pragma once
#include "../functional/functor.hpp"
#include "../get_type.hpp"
#include "atomic/class.hpp"
#include "non_union_class.hpp"
#include "union.hpp"

namespace PP
{
	namespace concepts
	{
		template <typename T>
		concept class_type =
			is_class(PP::type<T>) || non_union_class<T> || union_type<T>;
	}
}
