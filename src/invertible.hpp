#pragma once

namespace detail::invertible
{
	template <typename T>
	concept x = requires (T t)
	{
		{ -t } -> T;
	};
}
template <typename T>
struct invertible : value_t<detail::invertible::x<T>> {};