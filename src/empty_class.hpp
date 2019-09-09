#pragma once
#include "val.hpp"
#include "class_type.hpp"

namespace dempty_type
{
    template <typename T>
    struct x : T { char x; };
}
template <typename T>
requires class_type<T>::v
using empty_class = val<sizeof(dempty_type::x<T>) == 1>;