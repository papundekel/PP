#pragma once
#include <PP/get_type.hpp>
#include <PP/overloaded.hpp>
#include <PP/remove_cv.hpp>
#include <PP/type_t.hpp>

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
