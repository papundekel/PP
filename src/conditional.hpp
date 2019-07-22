#pragma once

namespace detail
{
	template <bool test, typename T, typename U>
	struct conditional { using type = T; };

	template <typename T, typename U>
	struct conditional<false, T, U> { using type = U; };
}

template <bool test, typename T, typename U>
using conditional = typename detail::conditional<test, T, U>::type;