#pragma once
#include "same.hpp"

namespace PP
{
	template <typename T>
	concept nonvoid = !same<T, void>;
}
