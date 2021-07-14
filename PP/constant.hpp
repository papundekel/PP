#pragma once
#include "forward_wrap.hpp"
#include "functor.hpp"

namespace PP
{
	namespace detail
	{
		constexpr auto constant_helper(auto&& x) noexcept
		{
			return PP_FORWARD(x);
		}
		template <typename T>
		constexpr auto&& constant_helper(const forward_wrap<T>& x) noexcept
		{
			return x.unwrap_forward();
		}
	}
	PP_FUNCTOR(constant, auto&& c)
	{
		return functor(
			[c = PP_FORWARD(c)](auto&&...) -> decltype(auto)
			{
				return detail::constant_helper(c);
			});
	});
}
