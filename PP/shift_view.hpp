#pragma once
#include "simple_view.hpp"
#include "size_t.hpp"

namespace PP
{
struct shift
{
	size_t value;
};

inline namespace literals
{
constexpr auto operator""_s(unsigned long long value)
{
	return shift(value);
}
}

constexpr auto operator>>(shift offset, concepts::view auto&& v)
{
	return simple_view(view::begin(PP_F(v)) + offset.value, view::end(PP_F(v)));
}
constexpr auto operator<<(concepts::view auto&& v, shift offset)
{
	return simple_view(view::begin(PP_F(v)), view::end(PP_F(v)) - offset.value);
}
}
