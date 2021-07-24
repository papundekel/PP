#pragma once
#include "../compose.hpp"
#include "../get_type.hpp"
#include "../overloaded.hpp"
#include "../remove_cv.hpp"

namespace PP
{
constexpr inline auto is_pointer = make_overloaded_pack(
									   []<typename T>(type_t<T*>)
									   {
										   return true;
									   },
									   [](auto)
									   {
										   return false;
									   }) |
                                   remove_cv;

PP_CONCEPT1(pointer)
}
