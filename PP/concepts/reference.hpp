#pragma once
#include "../functional/functor.hpp"
#include "returnable.hpp"
#include "void.hpp"
#include "complete_object.hpp"

namespace PP
{
	constexpr inline auto is_reference = is_returnable && !is_void_type && !is_complete_object;

	namespace concepts
	{
		template <typename T>
		concept reference = is_reference(type_v<T>);
	}
}
