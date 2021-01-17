#pragma once
#include "get_value.hpp"
#include "type_t.hpp"

namespace PP
{
	template <auto generator>
	class generator_tuple
	{
	public:
		constexpr decltype(auto) operator[](value_wrap auto i) const noexcept
		{
			return generator(PP_GET_VALUE(i));
		}
	};

	template <auto generator>
	constexpr auto tuple_count_implementation(generator_tuple<generator> t) noexcept
	{
		return value_v<std::size_t(0) - 1>;
	}

	template <auto generator>
	constexpr auto element_implementation(value_wrap auto i, generator_tuple<generator> t) noexcept
	{
		return PP_DECLTYPE(t[i]);
	}
}
