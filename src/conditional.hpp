#pragma once
#include "type_t.hpp"

namespace detail
{
	template <bool test, typename T, typename U>
	struct conditional : type_t<T> {};

	template <typename T, typename U>
	struct conditional<false, T, U> : type_t<U> {};
}

template <bool test, typename T, typename U>
using conditional = detail::conditional<test, T, U>::type;