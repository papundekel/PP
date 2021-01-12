#pragma once
#include "value_t.hpp"

namespace PP
{
	template <typename T>
	struct type_t
	{
		using type = T;

		constexpr auto operator->() const noexcept;
	};
	template <typename T>
	constexpr inline type_t<T> type_v = {};

	template <typename T, typename U>
	constexpr auto operator==(type_t<T>, type_t<U>) noexcept
	{
		return false;
	}
	template <typename T>
	constexpr auto operator==(type_t<T>, type_t<T>) noexcept
	{
		return true;
	}

	constexpr auto operator==(auto a, auto b) noexcept
	requires requires { typename decltype(a)::type; }
	{
		return true;
	}


	template <auto I>
	requires (I == 0)
	constexpr auto get(value_t<I>, type_t<auto> t) noexcept
	{
		return t;
	}
	constexpr std::size_t size_implementation(auto t) noexcept
	requires requires { typename decltype(t)::type::type; }
	{
		return 1;
	}

	#define PP_TYPE_UNSAFE(x) decltype(x)::type
	#define PP_DECLTYPE(x) (::PP::type_v<decltype(x)>)
}
