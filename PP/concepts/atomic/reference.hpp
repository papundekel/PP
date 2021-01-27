#pragma once
#include "../../functional/functor.hpp"
#include "../../functional/negate.hpp"
#include "../../macros/simple_concept.hpp"
#include "../void.hpp"
#include "complete_object.hpp"
#include "returnable.hpp"

namespace PP
{
	constexpr inline auto is_reference = is_returnable && !is_void && !is_complete_object;
}
