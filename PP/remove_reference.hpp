#pragma once
#include "apply_partially_first.hpp"
#include "compose.hpp"
#include "decompose_reference.hpp"
#include "tuple_get.hpp"
#include "value_t.hpp"

namespace PP
{
	constexpr inline auto remove_reference =
		tuple_get * value_0 | decompose_reference;

	constexpr auto operator!(concepts::type auto t) noexcept
	{
		return remove_reference(t);
	}
}
