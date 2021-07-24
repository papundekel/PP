#pragma once
#include "../applier.hpp"
#include "../apply_partially_first.hpp"
#include "../containers/tuple.hpp"
#include "concept.hpp"

namespace PP::tuple
{
constexpr inline auto make = *make_tuple;

constexpr inline auto forward = *forward_as_tuple;
}

constexpr auto operator!(PP::concepts::tuple auto&& t)
{
	return PP::tuple::make(PP_F(t));
}

constexpr auto operator+(concepts::tuple auto&& t) noexcept
{
	return PP::tuple::forward(PP_F(t));
}
