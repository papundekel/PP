#pragma once
#include "iterate_tuple.hpp"

namespace PP
{
	template <typename T>
	class singular_tuple : public iterate_tuple<value_t<1>, T>
	{
	public:
		constexpr singular_tuple(placeholder_t, auto&& value)
			: iterate_tuple<value_t<1>, T>(placeholder, PP_F(value))
		{}
		constexpr singular_tuple(placeholder_t,
		                         concepts::type auto,
		                         auto&& value)
			: singular_tuple(placeholder, PP_F(value))
		{}
	};
	template <typename T>
	singular_tuple(placeholder_t, T) -> singular_tuple<T>;
	singular_tuple(placeholder_t, concepts::type auto t, auto&&)
		-> singular_tuple<PP_GT(t)>;

	PP_FUNCTOR(make_singular_tuple, auto&& x)
	{
		return singular_tuple(placeholder, PP_F(x));
	});
	PP_FUNCTOR(forward_as_singular_tuple, auto&& x) noexcept
	{
		return singular_tuple(placeholder, PP_DECLTYPE(x), PP_F(x));
	});
}
