#pragma once
#include "type_t.hpp"
#include "overloaded.hpp"
#include "functional/functor.hpp"

namespace PP
{
	namespace detail
	{
		template <typename T>
		concept has_value_f = requires
		{
			T::value_f();
		};
		template <typename T>
		concept has_value = requires
		{
			T::value;
		};

		struct get_value__no_value_member {};
	}

	constexpr inline functor get_value
	{
		overloaded
		{
			[]<detail::has_value_f T>(type_t<T>) -> decltype(auto)
			{
				return T::value_f();
			},
			[]<detail::has_value T>(type_t<T>) -> decltype(auto)
			requires (!detail::has_value_f<T>)
			{
				return (T::value);
			},
			[](auto&&)
			{
				return detail::get_value__no_value_member{};
			}
		}
	};

	constexpr decltype(auto) operator-(type_t<auto> t) noexcept
	{
		return get_value(t);
	}
}
