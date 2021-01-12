#pragma once
#include "../functional/functor.hpp"
#include "../get_type.hpp"
#include "../overloaded.hpp"
#include "../templated_dummy.hpp"

namespace PP
{
	PP_FUNCTOR(is_unbounded_array, auto t)
	{
		return overloaded
		{
			[]<typename T>(type_t<T[]>) { return true; },
			[](auto t) { return false; }
		}(to_type_t(t));
	}};

	namespace concepts
	{
		template <typename T>
		concept unbounded_array = is_unbounded_array(type_v<T>);
	}
}
