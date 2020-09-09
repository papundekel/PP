#pragma once
#include "value_t.h"

namespace PP
{
	template <typename... T>
	using sizeof_many = value_t<sizeof...(T)>;
}
