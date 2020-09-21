#pragma once
#include <type_traits>
#include "function_info.hpp"

namespace PP
{	
	constexpr inline auto get_function_info = [](auto t) { return function_info(t); };
}
