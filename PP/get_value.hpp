#pragma once
#include "decl_type.hpp"
#include "functional/functor.hpp"
#include "get_type.hpp"
#include "overloaded.hpp"
#include "value_t.hpp"

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
		concept has_value = !has_value_f<T> && requires
		{
			T::value;
		};
	}

	template <typename T>
	concept value_wrap = detail::has_value_f<T> || detail::has_value<T>;

	constexpr inline functor get_type_value{ overloaded
	{
		[](auto t) -> decltype(auto)
		requires detail::has_value_f<PP_GET_TYPE(t)>
		{
			return PP_GET_TYPE(t)::value_f();
		},
		[](auto t) -> decltype(auto)
		requires detail::has_value<PP_GET_TYPE(t)>
		{
			return (PP_GET_TYPE(t)::value);
		}
	}};

	constexpr inline auto get_value = get_type_value | decl_type_copy;

	constexpr decltype(auto) operator*(value_wrap auto v) noexcept
	{
		return get_value(v);
	}

	constexpr decltype(auto) operator-(type_wrap auto t) noexcept
	{
		return get_type_value(t);
	}

	#define PP_GET_VALUE(x) (-PP_DECLTYPE(x))
	#define PP_COPY_VALUE(x) (::PP::value_v<PP_GET_VALUE(x)>)

	constexpr auto operator==(value_wrap auto x, value_wrap auto y)
	{
		return value_v<PP_GET_VALUE(x) == PP_GET_VALUE(y)>;
	}
	constexpr auto operator<(value_wrap auto x, value_wrap auto y)
	{
		return value_v<PP_GET_VALUE(x) < PP_GET_VALUE(y)>;
	}
	constexpr auto operator+(value_wrap auto x, value_wrap auto y)
	{
		return value_v<PP_GET_VALUE(x) + PP_GET_VALUE(y)>;
	}
	constexpr auto operator-(value_wrap auto x, value_wrap auto y)
	{
		return value_v<PP_GET_VALUE(x) - PP_GET_VALUE(y)>;
	}
	constexpr auto operator-(value_wrap auto x)
	{
		return value_v<-PP_GET_VALUE(x)>;
	}
}
