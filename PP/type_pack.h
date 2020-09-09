#pragma once
#include "type_t.h"

template <typename... T>
struct type_pack
{
	using type = type_pack<T...>;
};
