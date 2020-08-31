#pragma once
#include <type_traits>
#include "same.hpp"

namespace Papo
{
	template <typename T, typename U>
	concept different_cvref = !same<std::remove_cvref_t<T>, U>;
}
