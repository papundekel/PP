#pragma once
#include <type_traits>
#include <utility>

#include "apply_transform.hpp"
#include "concepts/array.hpp"
#include "declval.hpp"
#include "functional/functor.hpp"
#include "iterator.hpp"
#include "remove_cvref.hpp"
#include "size_t.hpp"

namespace PP
{
	namespace detail
	{
		constexpr decltype(auto) view_begin(auto&& v)
		requires requires { { PP_FORWARD(v).begin() } -> concepts::iterator; }
		{
			return PP_FORWARD(v).begin();
		}
		constexpr auto view_begin(auto&& v)
		requires ((is_array | remove_cvref)(PP_DECLTYPE(v)))
		{
			return v;
		}
		constexpr decltype(auto) view_begin_nonmember(auto&& v)
		requires requires { { begin(PP_FORWARD(v)) } -> concepts::iterator; }
		{
			return begin(PP_FORWARD(v));
		}
		
		constexpr decltype(auto) view_end(auto&& v)
		requires requires { { PP_FORWARD(v).begin() } -> concepts::iterator; }
		{
			return PP_FORWARD(v).end();
		}
		constexpr auto view_end(auto&& v)
		requires ((is_bounded_array | remove_cvref)(PP_DECLTYPE(v)))
		{
			return v + sizeof(v);
		}
		constexpr decltype(auto) view_end_nonmember(auto&& v)
		requires requires { { begin(PP_FORWARD(v)) } -> concepts::iterator; }
		{
			return end(PP_FORWARD(v));
		}
	}
	
	PP_FUNCTOR(view_begin, auto&& v) -> decltype(auto)
		requires (
			requires { detail::view_begin(PP_FORWARD(v)); } ||
			requires { detail::view_begin_nonmember(PP_FORWARD(v)); })
	{
		if constexpr (requires { detail::view_begin(PP_FORWARD(v)); })
			return detail::view_begin(PP_FORWARD(v));
		else
			return detail::view_begin_nonmember(PP_FORWARD(v));
	}};
	PP_FUNCTOR(view_end, auto&& v) -> decltype(auto)
	requires (
		requires { detail::view_end(PP_FORWARD(v)); } ||
		requires { detail::view_end_nonmember(PP_FORWARD(v)); })
	{
		if constexpr (requires { detail::view_end(PP_FORWARD(v)); })
			return detail::view_end(PP_FORWARD(v));
		else
			return detail::view_end_nonmember(PP_FORWARD(v));
	}};

	namespace detail
	{
		PP_FUNCTOR(view_begin_iterator_pure, auto v)
		{
			return PP_DECLTYPE(view_begin(declval(v)));
		}};
	}
	
	PP_FUNCTOR(is_view, auto t)
	{
		return requires
		{
			{ view_begin(declval(t)) } -> concepts::iterator;
			{ view_end(declval(t)) } -> concepts::sentinel<PP_APPLY_TRANSFORM(detail::view_begin_iterator_pure, t)>;
		};
	}};

	namespace concepts
	{
		template <typename T>
		concept view = is_view(type_v<T>);
	}
	
	constexpr decltype(auto) count(concepts::view auto&& v)
	{
		if constexpr (requires { PP_FORWARD(v).count(); })
			return PP_FORWARD(v).count();
		else
			return view_end(PP_FORWARD(v)) - view_begin(PP_FORWARD(v));
	}

	constexpr bool empty(concepts::view auto&& v)
	{
		return view_begin(PP_FORWARD(v)) == view_end(PP_FORWARD(v));
	}

	PP_FUNCTOR(view_begin_iterator, auto v)
	requires concepts::view<PP_GET_TYPE(v)>
	{
		return detail::view_begin_iterator_pure(v);
	}};
	PP_FUNCTOR(view_end_iterator, auto v)
	requires concepts::view<PP_GET_TYPE(v)>
	{
		return PP_DECLTYPE(view_end(declval(v)));
	} };
	constexpr inline auto view_base = iterator_base | view_begin_iterator;

	namespace detail
	{
		template <typename T>
		struct initializer_list_wrapper : public std::initializer_list<T>
		{};
		template <typename T>
		constexpr decltype(auto) wrap_initializer_list(const std::initializer_list<T>& l)
		{
			return reinterpret_cast<const initializer_list_wrapper<T>&>(l);
		}
	}

	constexpr auto begin_end(auto&& v)
	{
		return std::make_pair(view_begin(PP_FORWARD(v)), view_end(PP_FORWARD(v)));
	}
}
