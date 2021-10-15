#pragma once
#include "get_type.hpp"
#include "overloaded.hpp"
#include "remove_cv.hpp"
#include "type_t.hpp"

namespace PP
{
PP_CIA remove_pointer = compose(overloaded(
                            []<typename T>(type_t<T*>)
                            {
                                return type<T>;
                            },
                            [](auto&& t)
                            {
                                return t;
                            }),
                        remove_cv);
}
