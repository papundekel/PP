#pragma once
#include "template_t.hpp"
#include "get_value.hpp"

namespace PP
{
	template <template <typename...> typename...>
	struct template_tuple
	{
		static constexpr std::size_t template_tuple_size = 0;
	};
	template <template <typename...> typename T, template <typename...> typename... Templates>
	struct template_tuple
	{
		constexpr auto operator[](auto i) const noexcept
		{
			constexpr auto I = PP_COPY_VALUE(i);

			if constexpr (I == value_0)
				return template_v<T>;
			else
				return template_tuple<Templates...>{}[I - value_1];
		}

		static constexpr std::size_t template_tuple_size = 1 + sizeof...(Templates);
	};

	template <template <typename...> typename... Templates>
	constexpr inline template_tuple<Templates...> template_tuple_v = {};

	template <template <typename...> typename... Templates>
	constexpr auto get(auto i, template_tuple<Templates...> t) noexcept
	{
		return t[i];
	};
	constexpr auto size_implementation(auto t) noexcept
	requires requires { PP_GET_TYPE(t)::template_tuple_size; }
	{
		return PP_GET_TYPE(t)::template_tuple_size;
	};
}
