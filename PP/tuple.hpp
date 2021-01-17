#pragma once
#include "decompose_template.hpp"
#include "get_value.hpp"
#include "tuple_recursive.hpp"
#include "tuple_head_no_get.hpp"

namespace PP
{
	template <typename...>
	struct tuple
	{
		constexpr decltype(auto) operator[](value_wrap auto i) & noexcept;
		constexpr decltype(auto) operator[](value_wrap auto i) const& noexcept;
		constexpr decltype(auto) operator[](value_wrap auto i) && noexcept;
		constexpr decltype(auto) operator[](value_wrap auto i) const&& noexcept;
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

		constexpr decltype(auto) operator[](value_wrap auto i) & noexcept;
		constexpr decltype(auto) operator[](value_wrap auto i) const& noexcept;
		constexpr decltype(auto) operator[](value_wrap auto i) && noexcept;
		constexpr decltype(auto) operator[](value_wrap auto i) const&& noexcept;
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

		constexpr decltype(auto) operator[](value_wrap auto i) & noexcept;
		constexpr decltype(auto) operator[](value_wrap auto i) const& noexcept;
		constexpr decltype(auto) operator[](value_wrap auto i) && noexcept;
		constexpr decltype(auto) operator[](value_wrap auto i) const&& noexcept;
	};

	template <typename... T>
	tuple(T...)->tuple<T...>;

	constexpr auto&& head_implementation(concepts::tuple auto&& t) noexcept
	{
		return PP_FORWARD(t).head;
	}
	constexpr auto head_element_implementation(concepts::tuple auto&& t) noexcept
	{
		return PP_DECLTYPE(PP_FORWARD(t).head);
	}
	constexpr auto&& pred_implementation(concepts::tuple auto&& t) noexcept
	{
		return PP_FORWARD(t).rest;
	}

	template <typename... T>
	constexpr auto tuple_count_implementation(const tuple<T...>& t) noexcept
	{
		return value_v<sizeof...(T)>;
	}

	constexpr decltype(auto) get(value_wrap auto i, concepts::tuple auto&& t) noexcept
	{
		return tuple_recursive(tuple_head_no_get, i, PP_FORWARD(t));
	}

	template <typename H>
	constexpr decltype(auto) tuple<H>::operator[](value_wrap auto i) & noexcept
	{
		return get(i, *this);
	}
	template <typename H>
	constexpr decltype(auto) tuple<H>::operator[](value_wrap auto i) && noexcept
	{
		return get(i, std::move(*this));
	}
	template <typename H>
	constexpr decltype(auto) tuple<H>::operator[](value_wrap auto i) const& noexcept
	{
		return get(i, *this);
	}
	template <typename H>
	constexpr decltype(auto) tuple<H>::operator[](value_wrap auto i) const&& noexcept
	{
		return get(i, std::move(*this));
	}
	template <typename H, typename R, typename... Rest>
	constexpr decltype(auto) tuple<H, R, Rest...>::operator[](value_wrap auto i) & noexcept
	{
		return get(i, *this);
	}
	template <typename H, typename R, typename... Rest>
	constexpr decltype(auto) tuple<H, R, Rest...>::operator[](value_wrap auto i) && noexcept
	{
		return get(i, std::move(*this));
	}
	template <typename H, typename R, typename... Rest>
	constexpr decltype(auto) tuple<H, R, Rest...>::operator[](value_wrap auto i) const& noexcept
	{
		return get(i, *this);
	}
	template <typename H, typename R, typename... Rest>
	constexpr decltype(auto) tuple<H, R, Rest...>::operator[](value_wrap auto i) const&& noexcept
	{
		return get(i, std::move(*this));
	}

	constexpr auto make_tuple(auto&&... x)
	{
		return tuple(PP_FORWARD(x)...);
	}
	constexpr auto forward_as_tuple(auto&&... x) noexcept
	{
		return tuple<decltype(x)...>(PP_FORWARD(x)...);
	}
}
