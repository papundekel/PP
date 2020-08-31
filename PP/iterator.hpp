#pragma once
#include "same.hpp"
#include "nonvoid.hpp"
#include "size_t.hpp"

namespace PP
{
	namespace detail
	{
		// workaround
		template <typename T, typename U>
		concept same_lr = same<T, U&>;

		template <typename T>
		concept has_operator_advance = requires (T t, size_t n)
		{
			{ t += n } -> same_lr<T>;
			// { t += n } -> same<T&>; // doesn't compile
		};
		template <typename T>
		concept has_operator_back = requires (T t, size_t n)
		{
			{ t -= n } -> same_lr<T>;
			// { t -= n } -> same<T&>; // doesn't compile
		};
	}

	constexpr auto operator+(detail::has_operator_advance auto t, size_t u)
	{
		t += u;
		return t;
	}
	constexpr auto operator-(detail::has_operator_back auto t, size_t u)
	{
		t -= u;
		return t;
	}
	constexpr auto& operator++(detail::has_operator_advance auto& t)
	{
		return t += 1;
	}
	constexpr auto& operator--(detail::has_operator_back auto& t)
	{
		return t -= 1;
	}

	template <typename Iterator>
	concept iterator = requires (Iterator i)
	{
		{ ++i } -> same<Iterator&>;
		{ *i } -> nonvoid;
	};

	template <typename Sentinel, typename Iterator>
	concept sentinel =
		iterator<Iterator> &&
		requires (const Iterator i, const Sentinel s)
		{
			{ i == s } -> same<bool>;
		};
}
