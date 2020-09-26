#pragma once
#include "tuple_apply.hpp"

namespace PP
{
	template <typename F, typename T>
	struct fold_wrap
	{
		F& f;
		T&& x;
	};

	template <typename T, typename F, typename U>
	constexpr auto operator*(T&& a, fold_wrap<F, U> b)
	{
		return fold_wrap{ b.f, b.f(std::forward<T>(a), std::forward<U>(b.x)) };
	}

	template <bool copy_f = true, bool copy_init = true>
	constexpr inline auto tuple_foldr =
		[](auto f, auto init)
		{
			return tuple_apply<>(
				[f = std::move(f), init = std::move(init)]<typename... T>(T&&... t) -> decltype(auto)
				{
					return (std::forward<T>(t) * ... * init);
				});
		};
}
