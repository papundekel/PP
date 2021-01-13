#pragma once
#include "decompose_template.hpp"
#include "get_value.hpp"
#include "tuple_size.hpp"

namespace PP
{
	template <typename...>
	struct tuple
	{
		constexpr decltype(auto) operator[](value_wrap auto i)&;
		constexpr decltype(auto) operator[](value_wrap auto i)&&;
	};

	namespace concepts
	{
		template <typename T>
		concept tuple = type_v<T>->Template == template_v<::PP::tuple>;
		template <typename T>
		concept nontuple = !tuple<T>;
	}

	template <typename H>
	struct tuple<H>
	{
		H head;

		tuple() = default;
		tuple(const tuple&) = default;
		tuple(tuple&&) = default;

		constexpr tuple(auto&& h)
			: head(PP_FORWARD(h))
		{}

		constexpr decltype(auto) operator[](value_wrap auto i) &;
		constexpr decltype(auto) operator[](value_wrap auto i) &&;
	};
	template <typename H, typename R, typename... Rest>
	struct tuple<H, R, Rest...>
	{
		H head;
		tuple<R, Rest...> rest;

		tuple() = default;
		tuple(const tuple&) = default;
		tuple(tuple&&) = default;

		constexpr tuple(auto&& h, auto&&... r)
			: head(PP_FORWARD(h))
			, rest(PP_FORWARD(r)...)
		{}

		constexpr decltype(auto) operator[](value_wrap auto i)&;
		constexpr decltype(auto) operator[](value_wrap auto i)&&;
	};

	constexpr decltype(auto) get(value_wrap auto i, concepts::tuple auto&& t) noexcept
	{
		constexpr auto I = PP_COPY_VALUE(i);

		if constexpr (I == value_0)
			return PP_FORWARD(t).head;
		else
			return get(I - value_1, PP_FORWARD(t).rest);
	}
	constexpr auto size_implementation(type_wrap auto t) noexcept
		requires concepts::tuple<PP_GET_TYPE(t)>
	{
		return tuple_size(t->types);
	};

	template <typename H>
	constexpr decltype(auto) tuple<H>::operator[](value_wrap auto i)&
	{
		return get(i, *this);
	}
	template <typename H>
	constexpr decltype(auto) tuple<H>::operator[](value_wrap auto i)&&
	{
		return get(i, std::move(*this));
	}
	template <typename H, typename R, typename... Rest>
	constexpr decltype(auto) tuple<H, R, Rest...>::operator[](value_wrap auto i) &
	{
		return get(i, *this);
	}
	template <typename H, typename R, typename... Rest>
	constexpr decltype(auto) tuple<H, R, Rest...>::operator[](value_wrap auto i)&&
	{
		return get(i, std::move(*this));
	}

	constexpr auto make_tuple(auto&&... x) noexcept
	{
		return tuple<PP_GET_TYPE(~PP_DECLTYPE(x))...>(PP_FORWARD(x)...);
	}
	constexpr auto forward_as_tuple(auto&&... x) noexcept
	{
		return tuple<decltype(x)...>(PP_FORWARD(x)...);
	}
}
