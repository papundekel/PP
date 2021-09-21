#pragma once
#include "size_t.hpp"
#include "tuple/concept.hpp"

namespace PP
{
template <size_t I>
constexpr decltype(auto) get(concepts::tuple auto&& t) noexcept
{
    return PP_F(t)[value<I>];
}
}
