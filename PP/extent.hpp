#pragma once
#include "compose.hpp"
#include "overloaded.hpp"
#include "size_t.hpp"
#include "to_type_t.hpp"

namespace PP
{
PP_CIA extent = compose(overloaded(
                            []<typename T, size_t N>(type_t<T[N]>)
                            {
                                return N;
                            },
                            [](auto)
                            {
                                return 0_z;
                            }),
                        to_type_t);
}
