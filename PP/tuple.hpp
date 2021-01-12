#pragma once
#include <tuple>
#include "type_t.hpp"
#include "template_t.hpp"

namespace PP::detail
{
	template <typename T>
	concept is_std_tuple = type_v<T>->Template == template_v<std::tuple>;
}

namespace std
{
	template <auto I>
	constexpr decltype(auto) get(PP::value_t<I>, PP::detail::is_std_tuple auto&& t) noexcept
	{
		return std::get<std::size_t(I)>(std::forward<decltype(t)>(t));
	}
}
