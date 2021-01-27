#pragma once
#include "../functional/apply_partially.hpp"
#include "../functional/operators.hpp"
#include "../functional/compose.hpp"
#include "../macros/simple_concept.hpp"
#include "../remove_cv.hpp"
#include "same.hpp"

namespace PP
{
	constexpr inline auto is_void = eql * type_void | remove_cv;

	PP_CONCEPT(void_type, void)

	namespace concepts
	{
		template <typename T>
		concept nonvoid = !void_type<T>;
	}
}
