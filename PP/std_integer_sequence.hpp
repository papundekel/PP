#pragma once
#include <utility>

#include "functional/functor.hpp"
#include "functional/compose.hpp"
#include "get_value.hpp"
#include "overloaded.hpp"
#include "remove_cvref.hpp"
#include "value_t.hpp"
#include "value_tuple.hpp"

namespace PP
{
	constexpr inline auto is_std_integer_sequence = functor{ overloaded
	{
		[]<typename T, T... Values>(type_t<std::integer_sequence<T, Values...>>) { return true; },
		[](auto t) { return false; }
	} } | remove_cvref;

	namespace concepts
	{
		template <typename T>
		concept std_integer_sequence = is_std_integer_sequence_info(type_v<T>);
	}
}

namespace std
{
	template <typename T, T... Values>
	constexpr decltype(auto) get(PP::value_wrap auto i, std::integer_sequence<T, Values...> s)
	{
		return get(i, PP::value_tuple_v<Values...>);
	}
	constexpr auto size_implementation(PP::type_wrap auto t)
	requires PP::concepts::std_integer_sequence<PP_GET_TYPE(t)>
	{
		return PP_GET_TYPE(~t)::size();
	}
}
