#pragma once
#include "../functional/apply_partially.hpp"
#include "../functional/comparisons.hpp"
#include "../functional/functor.hpp"
#include "../functional/negate.hpp"
#include "../remove_cvref.hpp"
#include "same.hpp"

namespace PP
{
	constexpr inline auto is_nonvoid = !equal(partial_tag, type_v<void>) | remove_cvref;

	namespace concepts
	{
		template <typename T>
		concept nonvoid = is_nonvoid(type_v<T>);
	}
}
