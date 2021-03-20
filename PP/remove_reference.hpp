#pragma once
#include "decompose_reference.hpp"
#include "functional/apply_partially_simple.hpp"
#include "functional/compose.hpp"
#include "tuple_get.hpp"
#include "value_t.hpp"

namespace PP
{
	constexpr inline auto remove_reference = tuple_get * value_0 | decompose_reference;

	constexpr auto operator!(concepts::type auto t) noexcept
	{
		return remove_reference(t);
	}
}
