#pragma once
#include "add_const.hpp"
#include "construct_pack.hpp"
#include "copy_cvref.hpp"
#include "decompose_template.hpp"
#include "get_value.hpp"
#include "placeholder.hpp"
#include "tuple_concept.hpp"
#include "type_tuple.hpp"
#include "value_sequence.hpp"

namespace PP
{
	namespace detail
	{
		template <typename, typename T>
		class tuple_wrap
		{
			friend class tuple_helper;

			T obj;

		public:
			constexpr tuple_wrap(auto&& i)
				: obj(PP_FORWARD(i))
			{}
			constexpr tuple_wrap(in_place_t, auto&& i)
				: obj(PP_FORWARD(i)())
			{}
		};

		template <typename, typename... T>
		class tuple_impl;
		template <auto... I, typename... T>
		class tuple_impl<value_sequence<I...>, T...>
			: private tuple_wrap<value_t<I>, T>...
		{
			friend class tuple_helper;

			static constexpr auto wrap_types =
				type_tuple<tuple_wrap<value_t<I>, T>&...>;
			static constexpr auto types = type_tuple<T...>;

		public:
			constexpr tuple_impl()
				: tuple_wrap<value_t<I>, T>()...
			{}

			constexpr tuple_impl(auto&&... args) requires(sizeof...(T) ==
														  sizeof...(args))
				: tuple_impl(placeholder, PP_FORWARD(args)...)
			{}
			constexpr tuple_impl(auto&& t)
				: tuple_wrap<value_t<I>, T>(PP_FORWARD(t)[value<I>])...
			{}
			constexpr tuple_impl(placeholder_t,
								 auto&&... args) requires(sizeof...(T) ==
														  sizeof...(args))
				: tuple_wrap<value_t<I>, T>(PP_FORWARD(args))...
			{}
			constexpr tuple_impl(in_place_t,
								 auto&&... is) requires(sizeof...(T) ==
														sizeof...(is))
				: tuple_wrap<value_t<I>, T>(in_place, PP_FORWARD(is))...
			{}

		protected:
			constexpr void assign_tuple(auto&& t)
			{
				(((tuple_wrap<value_t<I>, T>&)* this = PP_FORWARD(t)[value<I>]),
				 ...);
			}
		};

		template <typename... T>
		using tuple_base =
			tuple_impl<decltype(make_value_sequence(PP_SIZEOF___(T))), T...>;
	}
	template <typename... T>
	struct tuple
		: public detail::tuple_base<T...>
	{
		using detail::tuple_base<T...>::tuple_base;

		constexpr auto&& operator[](concepts::value auto i) & noexcept;
		constexpr auto&& operator[](concepts::value auto i) const& noexcept;
		constexpr auto&& operator[](concepts::value auto i) && noexcept;
		constexpr auto&& operator[](concepts::value auto i) const&& noexcept;

		constexpr auto element(concepts::value auto i) noexcept;
		constexpr auto element(concepts::value auto i) const noexcept;

		constexpr auto& operator=(concepts::tuple auto&& t)
		{
			assign_tuple(PP_FORWARD(t));
			return *this;
		}
	};
	template <typename... T>
	tuple(T...) -> tuple<T...>;
	template <typename... T>
	tuple(placeholder_t, T...) -> tuple<T...>;
	tuple(in_place_t, auto&&... i) -> tuple<decltype(i())...>;

	template <typename... T>
	constexpr auto tuple_count_impl(const tuple<T...>&) noexcept
	{
		return value<sizeof...(T)>;
	}

	namespace detail
	{
		struct tuple_helper
		{
			static constexpr auto&& get(concepts::value auto i,
										auto&& t) noexcept
			{
				auto& wrap = t.wrap_types[i](t);
				return copy_cvref(PP_DECLTYPE(t),
								  PP_DECLTYPE(wrap.obj))(wrap.obj);
			}
			static constexpr auto element(concepts::value auto i,
										  auto& t) noexcept
			{
				return copy_cv(PP_DECLTYPE(t), t.types[i]);
			}
		};
	}

	PP_FUNCTOR(make_tuple, auto&&... args)
	{
		return tuple(placeholder, PP_FORWARD(args)...);
	});
	PP_FUNCTOR(forward_as_tuple, auto&&... args)
	{
		return tuple<decltype(args)...>(placeholder, PP_FORWARD(args)...);
	});

	template <typename... T>
	constexpr auto&& PP::tuple<T...>::operator[](
		concepts::value auto i) & noexcept
	{
		return detail::tuple_helper::get(i, *this);
	}
	template <typename... T>
	constexpr auto&& PP::tuple<T...>::operator[](
		concepts::value auto i) && noexcept
	{
		return detail::tuple_helper::get(i, move(*this));
	}
	template <typename... T>
	constexpr auto&& PP::tuple<T...>::operator[](
		concepts::value auto i) const& noexcept
	{
		return detail::tuple_helper::get(i, *this);
	}
	template <typename... T>
	constexpr auto&& PP::tuple<T...>::operator[](
		concepts::value auto i) const&& noexcept
	{
		return detail::tuple_helper::get(i, move(*this));
	}
	template <typename... T>
	constexpr auto PP::tuple<T...>::element(concepts::value auto i) noexcept
	{
		return detail::tuple_helper::element(i, *this);
	}
	template <typename... T>
	constexpr auto PP::tuple<T...>::element(
		concepts::value auto i) const noexcept
	{
		return detail::tuple_helper::element(i, *this);
	}
}
