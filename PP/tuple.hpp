#pragma once
#include "decompose_template.hpp"
#include "concepts/same_except_cvref.hpp"
#include "get_value.hpp"
#include "tuple_head_no_get.hpp"
#include "tuple_recursive.hpp"

namespace PP
{
	template <typename...>
	struct tuple {};

	namespace concepts
	{
		template <typename T>
		concept PPtuple = PP::type<T>->Template == Template<PP::tuple>;
	}

	template <typename H>
	struct tuple<H>
	{
		H internal_head;

		tuple() = default;
		tuple(const tuple&) = default;
		tuple(tuple&&) = default;

		constexpr tuple(concepts::different_except_cvref<tuple> auto&& h)
			: internal_head(PP_FORWARD(h))
		{}

		constexpr decltype(auto) operator[](concepts::value auto i) & noexcept;
		constexpr decltype(auto) operator[](concepts::value auto i) const& noexcept;
		constexpr decltype(auto) operator[](concepts::value auto i) && noexcept;
		constexpr decltype(auto) operator[](concepts::value auto i) const&& noexcept;
	};
	template <typename H, typename R, typename... Rest>
	struct tuple<H, R, Rest...>
	{
		H internal_head;
		tuple<R, Rest...> internal_rest;

		tuple() = default;
		tuple(const tuple&) = default;
		tuple(tuple&&) = default;

		constexpr tuple(concepts::different_except_cvref<tuple> auto&& h, auto&&... r)
			: internal_head(PP_FORWARD(h))
			, internal_rest(PP_FORWARD(r)...)
		{}

		constexpr decltype(auto) operator[](concepts::value auto i) & noexcept;
		constexpr decltype(auto) operator[](concepts::value auto i) const& noexcept;
		constexpr decltype(auto) operator[](concepts::value auto i) && noexcept;
		constexpr decltype(auto) operator[](concepts::value auto i) const&& noexcept;
	};

	template <typename... T>
	tuple(T...) -> tuple<T...>;

	constexpr auto& head_implementation(concepts::PPtuple auto& t) noexcept
	{
		return t.internal_head;
	}
	constexpr auto&& head_implementation(concepts::PPtuple auto&& t) noexcept
	{
		return PP_FORWARD(t.internal_head);
	}
	constexpr auto head_element_implementation(concepts::PPtuple auto&& t) noexcept
	{
		return PP_DECLTYPE(t.internal_head);
	}
	constexpr auto&& pred_implementation(concepts::PPtuple auto&& t) noexcept
	{
		return PP_FORWARD(t).internal_rest;
	}

	template <typename... T>
	constexpr auto tuple_count_implementation(const tuple<T...>& t) noexcept
	{
		return value<sizeof...(T)>;
	}

	constexpr decltype(auto) get(concepts::value auto i, concepts::PPtuple auto&& t) noexcept
	{
		return tuple_recursive(tuple_head_no_get, i, PP_FORWARD(t));
	}

	template <typename H>
	constexpr decltype(auto) tuple<H>::operator[](concepts::value auto i) & noexcept
	{
		return get(i, *this);
	}
	template <typename H>
	constexpr decltype(auto) tuple<H>::operator[](concepts::value auto i) && noexcept
	{
		return get(i, move(*this));
	}
	template <typename H>
	constexpr decltype(auto) tuple<H>::operator[](concepts::value auto i) const& noexcept
	{
		return get(i, *this);
	}
	template <typename H>
	constexpr decltype(auto) tuple<H>::operator[](concepts::value auto i) const&& noexcept
	{
		return get(i, move(*this));
	}
	template <typename H, typename R, typename... Rest>
	constexpr decltype(auto) tuple<H, R, Rest...>::operator[](concepts::value auto i) & noexcept
	{
		return get(i, *this);
	}
	template <typename H, typename R, typename... Rest>
	constexpr decltype(auto) tuple<H, R, Rest...>::operator[](concepts::value auto i) && noexcept
	{
		return get(i, move(*this));
	}
	template <typename H, typename R, typename... Rest>
	constexpr decltype(auto) tuple<H, R, Rest...>::operator[](concepts::value auto i) const& noexcept
	{
		return get(i, *this);
	}
	template <typename H, typename R, typename... Rest>
	constexpr decltype(auto) tuple<H, R, Rest...>::operator[](concepts::value auto i) const&& noexcept
	{
		return get(i, move(*this));
	}

	PP_FUNCTOR(make_tuple, auto&&... x)
	{
		return tuple<PP_GET_TYPE(~PP_DECLTYPE(x))...>(PP_FORWARD(x)...);
	}};
	PP_FUNCTOR(forward_as_tuple, auto&&... x)
	{
		return tuple<decltype(x)...>(PP_FORWARD(x)...);
	}};
}
