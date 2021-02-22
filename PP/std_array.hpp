#pragma once
#include <array>

#include "functional/functor.hpp"
#include "functional/compose.hpp"
#include "get_value.hpp"
#include "overloaded.hpp"
#include "remove_cvref.hpp"
#include "value_t.hpp"

namespace PP
{
	constexpr inline auto is_std_array = functor(overloaded
	{
		[]<typename T, std::size_t N>(type_t<std::array<T, N>>) { return true; },
		[](auto t) { return false; }
	} } | remove_cvref;

	namespace concepts
	{
		template <typename T>
		concept std_array = is_std_array(type<T>);
	}
}

namespace std
{
	constexpr decltype(auto) get(PP::concepts::value auto i, PP::concepts::std_array auto&& a) noexcept
	{
		return std::get<(std::size_t)-PP_DECLTYPE(i)>(PP_FORWARD(a));
	}
	constexpr auto size_implementation(PP::concepts::type auto t)
	requires PP::concepts::std_array<PP_GET_TYPE(t)>
	{
		return tuple_size_v<PP_GET_TYPE(~t)>;
	}
}