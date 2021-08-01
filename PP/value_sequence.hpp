#pragma once
#include "get_value.hpp"
#include "size_t.hpp"

namespace PP
{
template <auto... I>
struct value_sequence
{};
}

namespace PP::detail
{
template <auto... I>
constexpr auto value_sequence_add_one(value_sequence<I...>) noexcept
{
	return value_sequence<I..., sizeof...(I)>{};
}

template <auto... I>
constexpr auto value_sequence_double(value_sequence<I...>,
                                     concepts::value auto add_one) noexcept
{
	auto doubled = value_sequence<I..., (sizeof...(I) + I)...>{};

	if constexpr (PP_GV(add_one))
		return value_sequence_add_one(doubled);
	else
		return doubled;
}

constexpr auto value_sequence_make(concepts::value auto i)
{
	if constexpr (PP_GV(i) == 0)
		return value_sequence<>{};
	else
		return value_sequence_double(value_sequence_make(i / value_2),
		                             i % value_2 != value_0);
}
}

namespace PP
{
PP_FUNCTOR(value_sequence_make, concepts::value auto i)
{
	return detail::value_sequence_make(i);
});
}
