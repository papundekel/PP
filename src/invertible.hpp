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
using invertible = value_t<dinvertible::x<T>>;