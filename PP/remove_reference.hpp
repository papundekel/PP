#pragma once
#include "apply_partially_first.hpp"
#include "compose.hpp"
#include "decompose_reference.hpp"
#include "tuple/get.hpp"
#include "value_t.hpp"

namespace PP
{
PP_CIA remove_reference = tuple::get * value_0 | decompose_reference;

constexpr auto operator!(concepts::type auto t) noexcept
{
	return remove_reference(t);
}
}
