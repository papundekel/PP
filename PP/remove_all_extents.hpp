#pragma once
#include "remove_extent.hpp"
#include "same.hpp"

namespace PP
{
namespace detail
{
static constexpr auto remove_all_extents_helper(concepts::type auto t) noexcept
{
	constexpr auto T = PP_COPY_TYPE(t);

	constexpr auto removed_extent = remove_extent(T);
	if constexpr (removed_extent == T)
		return removed_extent;
	else
		return remove_all_extents_helper(removed_extent);
}
}

constexpr inline auto remove_all_extents =
	functor(
		[](auto t)
		{
			return detail::remove_all_extents_helper(t);
		}) |
	to_type_t;
}
