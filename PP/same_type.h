#pragma once
#include <type_traits>
#include "value_t.h"

template <typename T>
struct same_type
{
	template <typename U>
	using get = value_t<std::is_same_v<T, U>>;
};
