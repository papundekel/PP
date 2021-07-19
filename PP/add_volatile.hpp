#pragma once
#include "compose.hpp"
#include "get_type.hpp"

namespace PP
{
	constexpr inline auto add_volatile = functor(
											 []<typename T>(type_t<T>)
											 {
												 return type<volatile T>;
											 }) |
	                                     to_type_t;
}
