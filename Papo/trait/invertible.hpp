#pragma once

namespace dinvertible
{
	template <typename T>
	concept x = requires (T t)
	{
		{ -t } -> T;
	};
}
template <typename T>
constexpr auto invertible = dinvertible::x<T>;