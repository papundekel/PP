#pragma once
#include "add_const.hpp"
#include "concepts/same_except_cvref.hpp"
#include "construct_pack.hpp"
#include "copy_cvref.hpp"
#include "decompose_template.hpp"
#include "get_value.hpp"
#include "placeholder.hpp"
#include "tuple_like.hpp"
#include "type_tuple.hpp"
#include "value_sequence.hpp"

namespace PP
{
	namespace detail
	{
		template <typename, typename T>
		struct tuple_wrap
		{
			T obj;
		};

		template <typename, typename... T>
		class tuple_impl;
		template <size_t... I, typename... T>
		class tuple_impl<value_sequence<I...>, T...> : tuple_wrap<value_t<I>, T>...
		{
			friend class tuple_helper;
			
			static constexpr auto wrap_types = type_tuple<tuple_wrap<value_t<I>, T>&...>;
			static constexpr auto types = type_tuple<T...>;

		public:
			constexpr tuple_impl()
				: tuple_wrap<value_t<I>, T>()...
			{}

			constexpr tuple_impl(placeholder_t, auto&&... args)
				: tuple_wrap<value_t<I>, T>(PP_FORWARD(args))...
			{}
			constexpr tuple_impl(auto&& t)
				: tuple_wrap<value_t<I>, T>(PP_FORWARD(t)[value<I>])...
			{}

			constexpr auto& operator=(concepts::tuple auto&& t)
			{
				(((tuple_wrap<value_t<I>, T>&)*this = PP_FORWARD(t)[value<I>]), ...);
				return *this;
			}
		};

		struct tuple_helper
		{
			static constexpr auto&& get(concepts::value auto i, auto&& t) noexcept
			{
				auto& wrap = t.wrap_types[i](t);
				return copy_cvref(PP_DECLTYPE(t), PP_DECLTYPE(wrap.obj))(wrap.obj);
			}
			static constexpr auto element(concepts::value auto i, auto& t) noexcept
			{
				return copy_cv(PP_DECLTYPE(t), t.types[i]);
			}
		};
		template <typename...T>
		using tuple_base = tuple_impl<decltype(make_value_sequence(PP_SIZEOF___(T))), T...>;
	}
	template <typename... T>
	struct tuple : public detail::tuple_base<T...>
	{
		using detail::tuple_base<T...>::tuple_base;

		constexpr auto&& operator[](concepts::value auto i)      &  noexcept;
		constexpr auto&& operator[](concepts::value auto i) const&  noexcept;
		constexpr auto&& operator[](concepts::value auto i)      && noexcept;
		constexpr auto&& operator[](concepts::value auto i) const&& noexcept;

		constexpr auto element(concepts::value auto i)       noexcept;
		constexpr auto element(concepts::value auto i) const noexcept;
	};
	template <typename... T>
	tuple(placeholder_t, T...) -> tuple<T...>;

	template <typename... T>
	constexpr auto tuple_count_implementation(const tuple<T...>&) noexcept
	{
		return value<sizeof...(T)>;
	}

	PP_FUNCTOR(make_tuple, auto&&... x)
	{
		return tuple(placeholder, PP_FORWARD(x)...);
	});
	PP_FUNCTOR(forward_as_tuple, auto&&... x)
	{
		return tuple<decltype(x)...>(placeholder, PP_FORWARD(x)...);
	});
}

template <typename... T>
constexpr auto&& PP::tuple<T...>::operator[](concepts::value auto i) & noexcept
{
	return detail::tuple_helper::get(i, *this);
}
template <typename... T>
constexpr auto&& PP::tuple<T...>::operator[](concepts::value auto i) && noexcept
{
	return detail::tuple_helper::get(i, move(*this));
}
template <typename... T>
constexpr auto&& PP::tuple<T...>::operator[](concepts::value auto i) const& noexcept
{
	return detail::tuple_helper::get(i, *this);
}
template <typename... T>
constexpr auto&& PP::tuple<T...>::operator[](concepts::value auto i) const&& noexcept
{
	return detail::tuple_helper::get(i, move(*this));
}
template <typename... T>
constexpr auto PP::tuple<T...>::element(concepts::value auto i) noexcept
{
	return detail::tuple_helper::element(i, *this);
}
template <typename... T>
constexpr auto PP::tuple<T...>::element(concepts::value auto i) const noexcept
{
	return detail::tuple_helper::element(i, *this);
}
