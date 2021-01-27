#pragma once
#include "concepts/equatable.hpp"
#include "concepts/same.hpp"
#include "concepts/void.hpp"
#include "functional/functor.hpp"
#include "size_t.hpp"

namespace PP
{
	namespace detail
	{
		template <typename T>
		concept has_operator_advance = requires (T t, size_t n)
		{
			{ t += n } -> concepts::same<T&>;
		};
		template <typename T>
		concept has_operator_back = requires (T t, size_t n)
		{
			{ t -= n } -> concepts::same<T&>;
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
	constexpr auto operator++(detail::has_operator_advance auto& t, int)
	{
		auto x = t;
		++t;
		return x;
	}
	constexpr auto& operator--(detail::has_operator_back auto& t)
	{
		return t -= 1;
	}
	constexpr auto operator--(detail::has_operator_back auto& t, int)
	{
		auto x = t;
		--t;
		return x;
	}
	
	PP_FUNCTOR(is_iterator, auto t)
	{
		return requires (PP_GET_TYPE(t) i)
		{
			++i;
			{ *i } -> concepts::nonvoid;
		};
	}};
	PP_CONCEPT1(iterator)

	namespace concepts
	{
		template <typename S, typename I>
		concept sentinel = iterator<I> && equatable<I, S>;
	}
	PP_FUNCTOR(is_sentinel, auto s, auto i)
	{
		return concepts::sentinel<PP_GET_TYPE(s), PP_GET_TYPE(i)>;
	}};

	PP_FUNCTOR(iterator_base, auto i)
	{
		return PP_DECLTYPE(*declval(i));
	}};
}
