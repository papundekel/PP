#pragma once
#include "iterator.hpp"

namespace PP
{
constexpr inline struct unbounded_t
{
} unbounded{};
}

constexpr bool operator==(PP::concepts::iterator auto, PP::unbounded_t) noexcept
{
	return false;
}
