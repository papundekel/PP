#pragma once
#include "value_t.hpp"
#include "remove_cv.hpp"

namespace dpointer_type
{
    template <typename T>
    struct x : value_t<false> {};
    template <typename T>
    struct x<T*> : value_t<true> {};
}
template <typename T>
using pointer_type = dpointer_type::x<remove_cv<T>>;