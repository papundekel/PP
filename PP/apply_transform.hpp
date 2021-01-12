#pragma once
#include "get_type.hpp"

namespace PP
{
	template <auto f, typename T>
	using apply_transform_t = PP_GET_TYPE((f)(type_v<T>));

	#define PP_APPLY_TRANSFORM(f, t) apply_transform_t<f, PP_GET_TYPE(t)>
}
