#pragma once
#include "type_t.hpp"
#include "get_type.hpp"

namespace PP
{
	template <typename T>
	using extract_type = type_t<get_type<T>>;
}
