#pragma once
#include <PP/remove_extent.hpp>
#include <PP/same.hpp>
#include <PP/to_type_t.hpp>

namespace PP
{
namespace detail
{
static constexpr auto remove_all_extents_helper(
    concepts::type auto&& t) noexcept
{
    constexpr auto T = PP_CT(t);

    constexpr auto removed_extent = remove_extent(T);
    if constexpr (removed_extent == T)
        return removed_extent;
    else
        return remove_all_extents_helper(removed_extent);
}
}

PP_CIA remove_all_extents = compose(
    [](auto t)
    {
        return detail::remove_all_extents_helper(t);
    },
    to_type_t);
}
