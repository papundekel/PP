#pragma once
#include "compose.hpp"
#include "get_type.hpp"
#include "overloaded.hpp"
#include "size_t.hpp"
#include "type_t.hpp"

namespace PP
{
PP_CIA remove_extent = make_overloaded_pack(
                           []<typename T, size_t N>(type_t<T[N]>)
                           {
                               return type<T>;
                           },
                           []<typename T>(type_t<T[]>)
                           {
                               return type<T>;
                           },
                           [](auto t)
                           {
                               return t;
                           }) |
                       to_type_t;
}
