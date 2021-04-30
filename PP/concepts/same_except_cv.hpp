#pragma once
#include "same.hpp"

namespace PP
{
	namespace concepts
	{
		template <typename T, typename U>
		concept same_except_cv =
			same<T, U> || same<T, const U> || same<T, volatile U> ||
			same<T, const volatile U>;

		template <typename T, typename U>
		concept different_except_cv = different<T, U>&& different<T, const U>&&
			different<T, volatile U>&& different<T, const volatile U>;
	}
}
