#pragma once
#include "../functional/apply_partially.hpp"
#include "../functional/comparisons.hpp"
#include "../functional/compose.hpp"
#include "../remove_cv.hpp"
#include "same.hpp"

namespace PP
{
	constexpr inline auto is_void = equal(partial_tag, type_v<void>) | remove_cv;

	namespace concepts
	{
		template <typename T>
		concept void_type = is_void(type_v<T>);
	}
}
