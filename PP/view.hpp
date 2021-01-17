#pragma once
#include "apply_transform.hpp"
#include "concepts/array.hpp"
#include "declval.hpp"
#include "functional/functor.hpp"
#include "iterator.hpp"
#include "remove_reference.hpp"
#include "size_t.hpp"

namespace PP
{
	namespace detail
	{
		template <typename T>
		concept view_has_member_begin = requires
		{
			{ declval(type_v<T>).begin() } -> concepts::iterator;
		};
		template <typename T>
		concept view_has_member_end = requires
		{
			{ declval(type_v<T>).end() } -> concepts::nonvoid;
		};
	}
	
	PP_FUNCTOR(view_begin, auto&& v) -> decltype(auto)
	requires
		requires view_has_member_begin<decltype(v)> ||
		requires (is_array(!PP_DECLTYPE(v))) ||
		requires requires { { begin(PP_FORWARD(v)) } -> concepts::iterator; }
	{
		if constexpr (view_has_member_begin<decltype(v)>)
			return PP_FORWARD(v).begin();
		else if constexpr (is_array(!PP_DECLTYPE(v)))
			return v + 0;
		else
			return begin(PP_FORWARD(v));
	}};
	PP_FUNCTOR(view_end, auto&& v) -> decltype(auto)
	requires
	requires view_has_member_end<decltype(v)> ||
	requires (is_bounded_array(!PP_DECLTYPE(v))) ||
	requires requires { { end(PP_FORWARD(v)) } -> concepts::nonvoid; }
	{
		if constexpr (view_has_member_end<decltype(v)>)
			return PP_FORWARD(v).end();
		else if constexpr (is_bounded_array(!PP_DECLTYPE(v)))
			return v + sizeof(v);
		else
			return end(PP_FORWARD(v));
	}};

	namespace detail
	{
		PP_FUNCTOR(view_begin_iterator_pure, auto v)
		{
			return PP_DECLTYPE(view_begin(declval(v)));
		}};
	}
	
	PP_FUNCTOR(is_view, type_wrap auto t)
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
