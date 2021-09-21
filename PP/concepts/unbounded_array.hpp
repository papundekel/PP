#pragma once
#include "../compose.hpp"
#include "../get_type.hpp"
#include "../overloaded.hpp"

namespace PP
{
PP_CIA is_unbounded_array = make_overloaded_pack(
                                []<typename T>(type_t<T[]>)
                                {
                                    return true;
                                },
                                [](auto)
                                {
                                    return false;
                                }) |
                            to_type_t;

PP_CONCEPT1(unbounded_array)
}
