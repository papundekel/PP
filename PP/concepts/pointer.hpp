#pragma once
#include "../compose.hpp"
#include "../get_type.hpp"
#include "../overloaded.hpp"
#include "../remove_cv.hpp"

namespace PP
{
PP_CIA is_pointer = compose(overloaded(
                        []<typename T>(type_t<T*>)
                        {
                            return true;
                        },
                        [](auto&&)
                        {
                            return false;
                        }),
                    remove_cv);

PP_CONCEPT1(pointer)
}
