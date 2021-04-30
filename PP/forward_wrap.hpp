#pragma once
#include "functional/functor.hpp"

namespace PP
{
	template <typename T>
	struct forward_wrap
	{
		T&& ref;

		constexpr T&& unwrap() const noexcept
		{
			return static_cast<T&&>(ref);
		}

		constexpr decltype(auto) operator()(auto&&... args) const noexcept
		{
			return static_cast<T&&>(ref)(PP_FORWARD(args)...);
		}
	};
	template <typename T>
	forward_wrap(T&&) -> forward_wrap<T>;

	constexpr auto&& unwrap(auto&& x)
	{
		return PP_FORWARD(x);
	}
	template <typename T>
	constexpr auto&& unwrap(const forward_wrap<T>& x)
	{
		return x.unwrap();
	}

#define PP_FORWARD_WRAP(x)                                                     \
	::PP::forward_wrap                                                         \
	{                                                                          \
		PP_FORWARD(x)                                                          \
	}

	PP_FUNCTOR(fwrap, auto&& x)
	{
		return PP_FORWARD_WRAP(x);
	});
}
