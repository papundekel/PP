#pragma once
#include "get_type.hpp"
#include "get_value.hpp"
#include "placeholder.hpp"
#include "utility/forward.hpp"
#include "value_t.hpp"

namespace PP
{
	template <typename Count, typename T>
	class iterate_tuple
	{
	public:
		T obj;

		constexpr iterate_tuple(placeholder_t, auto&& obj)
			: obj(PP_F(obj))
		{}
		constexpr iterate_tuple(placeholder_t, concepts::value auto, auto&& obj)
			: iterate_tuple(placeholder, PP_F(obj))
		{}
		constexpr iterate_tuple(placeholder_t,
		                        concepts::value auto,
		                        concepts::type auto,
		                        auto&& obj)
			: iterate_tuple(placeholder, PP_F(obj))
		{}

		constexpr auto tuple_count() const noexcept
		{
			return value<-type<Count>>;
		}
		constexpr auto element(concepts::value auto) const noexcept
		{
			return type<T>;
		}
		constexpr decltype(auto) operator[](concepts::value auto i) & noexcept;
		constexpr decltype(auto) operator[](
			concepts::value auto i) const& noexcept;
		constexpr decltype(auto) operator[](concepts::value auto i) && noexcept;
		constexpr decltype(auto) operator[](
			concepts::value auto i) const&& noexcept;
	};
	template <typename T>
	iterate_tuple(placeholder_t, concepts::value auto count, T)
		-> iterate_tuple<decltype(to_value_t(count)), T>;
	iterate_tuple(placeholder_t,
	              concepts::value auto count,
	              concepts::type auto t,
	              auto&&)
		-> iterate_tuple<decltype(to_value_t(count)), PP_GT(t)>;

	template <typename Count, typename T>
	constexpr auto& get(concepts::value auto,
	                    iterate_tuple<Count, T>& t) noexcept
	{
		return t.obj;
	}
	template <typename Count, typename T>
	constexpr const auto& get(concepts::value auto,
	                          const iterate_tuple<Count, T>& t) noexcept
	{
		return t.obj;
	}
	template <typename Count, typename T>
	constexpr auto&& get(concepts::value auto,
	                     iterate_tuple<Count, T>&& t) noexcept
	{
		return PP_F(t.obj);
	}
	template <typename Count, typename T>
	constexpr const auto&& get(concepts::value auto,
	                           const iterate_tuple<Count, T>&& t) noexcept
	{
		return static_cast<const decltype(t.obj)&&>(t.obj);
	}

	PP_FUNCTOR(make_iterate_tuple, concepts::value auto count, auto&& x)
	{
		return iterate_tuple(placeholder, count, PP_F(x));
	});
	PP_FUNCTOR(forward_as_iterate_tuple, concepts::value auto count, auto&& x)
	noexcept
	{
		return iterate_tuple(placeholder, count, PP_DECLTYPE(x), PP_F(x));
	});
}

template <typename Count, typename T>
constexpr decltype(auto) PP::iterate_tuple<Count, T>::operator[](
	concepts::value auto i) & noexcept
{
	return get(i, *this);
}
template <typename Count, typename T>
constexpr decltype(auto) PP::iterate_tuple<Count, T>::operator[](
	concepts::value auto i) const& noexcept
{
	return get(i, *this);
}
template <typename Count, typename T>
constexpr decltype(auto) PP::iterate_tuple<Count, T>::operator[](
	concepts::value auto i) && noexcept
{
	return get(i, move(*this));
}
template <typename Count, typename T>
constexpr decltype(auto) PP::iterate_tuple<Count, T>::operator[](
	concepts::value auto i) const&& noexcept
{
	return get(i, move(*this));
}
