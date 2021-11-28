#pragma once
#include <PP/size_t.hpp>
#include <PP/tuple/concept.hpp>

namespace PP
{
namespace tuple
{
template <size_t I>
constexpr decltype(auto) get(concepts::tuple auto&& t) noexcept
{
    return PP_F(t)[value<I>];
}
}
}
