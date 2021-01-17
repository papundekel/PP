#pragma once
#include "../type_t.hpp"

namespace PP::concepts
{
	template <typename T, typename U>
	concept same = type_v<T> == type_v<U> && type_v<U> == type_v<T>;
	template <typename T, typename U>
	concept different = !same<T, U>;
}
