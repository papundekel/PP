#pragma once
#include "functional/compose.hpp"
#include "overloaded.hpp"
#include "get_type.hpp"

namespace PP
{
	namespace detail
	{
		constexpr inline functor remove_reference_helper
		{
			overloaded
			{
				[]<typename T>(type_t<T  >) { return type_v<T>; },
				[]<typename T>(type_t<T& >) { return type_v<T>; },
				[]<typename T>(type_t<T&&>) { return type_v<T>; }
			}
		};
	}

	constexpr inline auto remove_reference = detail::remove_reference_helper | to_type_t;
}
