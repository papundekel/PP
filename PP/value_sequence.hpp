#pragma once
#include "get_value.hpp"
#include "size_t.hpp"

namespace PP
{
template <auto... I>
struct value_sequence
{};

namespace detail
{
template <auto... I>
constexpr auto double_value_sequence(value_sequence<I...>,
                                     concepts::value auto add_one) noexcept
{
	if constexpr (PP_GV(add_one))
		return value_sequence<I..., (sizeof...(I) + I)..., 2 * sizeof...(I)>{};
	else
		return value_sequence<I..., (sizeof...(I) + I)...>{};
}

constexpr auto make_value_sequence(concepts::value auto i)
{
	if constexpr (PP_GV(i) == 0)
		return value_sequence<>{};
	else
		return double_value_sequence(make_value_sequence(i / value_2),
		                             i % value_2 != value_0);
}
}

PP_FUNCTOR(make_value_sequence, concepts::value auto i)
{
	return detail::make_value_sequence(i);
});
}
