#pragma once
#include "type_t.hpp"
#include "functional/functor.hpp"
#include "overloaded.hpp"

namespace PP
{
	constexpr inline functor remove_cv
	{
		overloaded
		{
			[]<typename T>(type_t<               T>) { return type_v<T>; },
			[]<typename T>(type_t<const          T>) { return type_v<T>; },
			[]<typename T>(type_t<      volatile T>) { return type_v<T>; },
			[]<typename T>(type_t<const volatile T>) { return type_v<T>; }
		}
	};
}
