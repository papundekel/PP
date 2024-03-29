#pragma once
#include <PP/compose.hpp>
#include <PP/overloaded.hpp>
#include <PP/to_type_t.hpp>

namespace PP
{
PP_CIA is_unbounded_array = compose(overloaded(
                                        []<typename T>(type_t<T[]>)
                                        {
                                            return true;
                                        },
                                        [](auto&&)
                                        {
                                            return false;
                                        }),
                                    to_type_t);

PP_CONCEPT1(unbounded_array)
}
