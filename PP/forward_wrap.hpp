#pragma once
#include "utility/forward.hpp"

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
	};
	template <typename T>
	forward_wrap(T&&) -> forward_wrap<T>;

	#define PP_FORWARD_WRAP(x) ::PP::forward_wrap{PP_FORWARD(x)}
}
