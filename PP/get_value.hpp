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

	namespace concepts
	{
		template <typename T>
		concept value = detail::has_value_f<T> || detail::has_value<T>;
	}

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

	constexpr decltype(auto) operator*(concepts::value auto v) noexcept
	{
		return get_value(v);
	}

	constexpr decltype(auto) operator-(concepts::type auto t) noexcept
		requires requires { get_type_value(t); }
	{
		return get_type_value(t);
	}

	#define PP_GET_VALUE(x) (-PP_DECLTYPE(x))
	#define PP_COPY_VALUE(x) (::PP::value<PP_GET_VALUE(x)>)
	#define PP_GET_VALUE_TYPE(x) PP_DECLTYPE(PP_GET_VALUE(x))

	constexpr auto operator==(concepts::value auto x, concepts::value auto y)
	{
		return value<PP_GET_VALUE(x) == PP_GET_VALUE(y)>;
	}
	constexpr auto operator<(concepts::value auto x, concepts::value auto y)
	{
		return value<PP_GET_VALUE(x) <  PP_GET_VALUE(y)>;
	}
	constexpr auto operator<=(concepts::value auto x, concepts::value auto y)
	{
		return value<PP_GET_VALUE(x) <= PP_GET_VALUE(y)>;
	}
	constexpr auto operator>(concepts::value auto x, concepts::value auto y)
	{
		return value<(PP_GET_VALUE(x) >  PP_GET_VALUE(y))>;
	}
	constexpr auto operator>=(concepts::value auto x, concepts::value auto y)
	{
		return value<(PP_GET_VALUE(x) >= PP_GET_VALUE(y))>;
	}
	constexpr auto operator+(concepts::value auto x, concepts::value auto y)
	{
		return value<PP_GET_VALUE(x) +  PP_GET_VALUE(y)>;
	}
	constexpr auto operator-(concepts::value auto x, concepts::value auto y)
	{
		return value<PP_GET_VALUE(x) -  PP_GET_VALUE(y)>;
	}
	constexpr auto operator-(concepts::value auto x)
	{
		return value<-PP_GET_VALUE(x)>;
	}
	constexpr auto operator&&(concepts::value auto x, concepts::value auto y)
	{
		return value<PP_GET_VALUE(x) && PP_GET_VALUE(y)>;
	}
	constexpr auto operator||(concepts::value auto x, concepts::value auto y)
	{
		return value<PP_GET_VALUE(x) || PP_GET_VALUE(y)>;
	}

	constexpr auto operator<=(concepts::type auto x, concepts::type auto y)
	requires requires { -x; -y; }
	{
		return -x <= -y;
	}

	PP_FUNCTOR(to_value_t, concepts::value auto x)
	{
		return value<PP_GET_VALUE(x)>;
	}};
}
