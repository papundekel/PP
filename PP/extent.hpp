#pragma once
#include <PP/compose.hpp>
#include <PP/overloaded.hpp>
#include <PP/size_t.hpp>
#include <PP/to_type_t.hpp>

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
