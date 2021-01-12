#pragma once
#include <type_traits>
#include <utility>

#include "always_false.hpp"
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
		template <typename T>
		concept has_begin = requires
		{
			{ declval(type_v<T>).begin() } -> concepts::iterator;
		};
		template <typename T>
		concept has_end = requires
		{
			declval(type_v<T>).end();
		};
	}
	constexpr auto begin(auto&& v)
	{
		if constexpr (requires { { PP_FORWARD(v).begin() } -> concepts::iterator; })
			return PP_FORWARD(v).begin();
		else if constexpr ((is_array | remove_cvref)(PP_DECLTYPE(v)))
			return v;
		else
			static_assert(always_false<decltype(v)>);
	}
	constexpr auto end(auto&& v)
	{
		if constexpr (requires { { PP_FORWARD(v).end() } -> concepts::nonvoid; })
			return PP_FORWARD(v).end();
		else if constexpr ((is_bounded_array | remove_cvref)(PP_DECLTYPE(v)))
			return v + sizeof(v);
		else
			static_assert(always_false<decltype(v)>);
	}

	namespace detail
	{
		PP_FUNCTOR(view_begin_iterator_pure, auto v)
		{
			return PP_DECLTYPE(begin(declval(v)));
		}};
	}
	
	PP_FUNCTOR(is_view, auto v)
	{
		return requires
		{
			{ begin(declval(v)) } -> concepts::iterator;
			{ end(declval(v)) } -> concepts::sentinel<PP_APPLY_TRANSFORM(detail::view_begin_iterator_pure, v)>;
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
			return end(PP_FORWARD(v)) - begin(PP_FORWARD(v));
	}

	constexpr bool empty(concepts::view auto&& v)
	{
		return begin(PP_FORWARD(v)) == end(PP_FORWARD(v));
	}

	PP_FUNCTOR(view_begin_iterator, auto v)
	requires concepts::view<PP_GET_TYPE(v)>
	{
		return detail::view_begin_iterator_pure(v);
	}};
	PP_FUNCTOR(view_end_iterator, auto v)
	requires concepts::view<PP_GET_TYPE(v)>
	{
		return PP_DECLTYPE(end(declval(v)));
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
		return std::make_pair(begin(PP_FORWARD(v)),	end(PP_FORWARD(v)));
	}
}
