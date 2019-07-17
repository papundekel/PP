#pragma once

template <auto val>
struct value_t
{
	static constexpr auto value = val;
	using type = decltype(val);
};