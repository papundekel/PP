#pragma once
#include "concepts/equatable.hpp"
#include "concepts/same.hpp"
#include "concepts/void.hpp"
#include "functional/functor.hpp"
#include "ptrdiff_t.hpp"

namespace PP
{
	namespace detail
	{
		template <typename T>
		concept has_step = requires (T t)
		{
			{ t.step() } -> concepts::same<void>;
		};
		template <typename T>
		concept has_step_back = requires (T t)
		{
			{ t.step_back() } -> concepts::same<void>;
		};
		template <typename T>
		concept has_advance = requires (T t, ptrdiff_t n)
		{
			{ t.advance(n) } -> concepts::same<void>;
		};

		template <typename T>
		concept has_step_or_advance = has_step<T> || has_advance<T>;
		template <typename T>
		concept has_step_back_or_advance = has_step_back<T> || has_advance<T>;
	}

	constexpr auto& operator+=(detail::has_step_or_advance auto&& t, ptrdiff_t offset)
	{
		if constexpr (detail::has_advance<decltype(t)>)
			t.advance(offset);
		else
		{
			for (ptrdiff_t i = 0; i != offset; ++i)
				t.step();
		}

		return t;
	}
	constexpr auto& operator-=(detail::has_step_back_or_advance auto&& t, ptrdiff_t offset)
	{
		if constexpr (detail::has_advance<decltype(t)>)
			t.advance(-offset);
		else
		{
			for (ptrdiff_t i = 0; i != offset; ++i)
				t.step_back();
		}

		return t;
	}

	namespace detail
	{
		template <typename T>
		concept has_operator_advance = requires (T t, ptrdiff_t n)
		{
			{ t += n } -> concepts::same<T&>;
		};
		template <typename T>
		concept has_operator_back = requires (T t, ptrdiff_t n)
		{
			{ t -= n } -> concepts::same<T&>;
		};
	}

	constexpr auto operator+(detail::has_operator_advance auto t, ptrdiff_t offset)
	{
		t += offset;
		return t;
	}
	constexpr auto operator-(detail::has_operator_back auto t, ptrdiff_t offset)
	{
		t -= offset;
		return t;
	}
	constexpr auto& operator++(detail::has_step_or_advance auto& t)
	{
		if constexpr (detail::has_advance<decltype(t)>)
			t += 1;
		else
			t.step();

		return t;
	}
	constexpr auto operator++(detail::has_step_or_advance auto& t, int)
	{
		auto x = t;
		++t;
		return x;
	}
	constexpr auto& operator--(detail::has_operator_back auto& t)
	{
		if constexpr (detail::has_advance<decltype(t)>)
			t -= 1;
		else
			t.step_back();

		return t;
	}
	constexpr auto operator--(detail::has_operator_back auto& t, int)
	{
		auto x = t;
		--t;
		return x;
	}

	namespace concepts
	{
		template <typename T>
		concept iterator = requires (T i)
		{
			++i;
			{ *i } -> nonvoid;
		} && equatable<T, T>;
	}
	PP_CONCEPT_FUNCTOR(iterator)

	namespace concepts
	{
		template <typename T>
		concept iterator_bi = requires (T i)
		{
			--i;
		} && iterator<T>;
	}
	PP_CONCEPT_FUNCTOR(iterator_bi)

	namespace concepts
	{
		template <typename T>
		concept iterator_ra = requires (T i)
		{
			i += ptrdiff_t(0);
			{ i[ptrdiff_t(0)] } -> nonvoid;
			i - i;
		} && iterator_bi<T>;
	}
	PP_CONCEPT_FUNCTOR(iterator_ra)

	namespace concepts
	{
		template <typename S, typename I>
		concept sentinel = iterator<I> && equatable<I, S>;
	}
	PP_FUNCTOR(is_sentinel, auto s, auto i)
	{
		return concepts::sentinel<PP_GET_TYPE(s), PP_GET_TYPE(i)>;
	});

	PP_FUNCTOR(iterator_base, auto i)
	{
		return PP_DECLTYPE(*declval(i));
	});

	PP_FUNCTOR(iterator_prev, concepts::iterator_bi auto i)
	{
		--i;
		return i;
	});
	PP_FUNCTOR(iterator_next, concepts::iterator auto i)
	{
		++i;
		return i;
	});
}
