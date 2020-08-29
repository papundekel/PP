#pragma once
#include "same.hpp"

namespace Papo
{
	template <typename T>
	concept nonvoid = !same<T, void>;
}
