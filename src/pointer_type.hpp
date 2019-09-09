#pragma once
#include "val.hpp"
#include "remove_cv.hpp"

namespace dpointer_type
{
    template <typename T>
    constexpr auto x = false;
    template <typename T>
    constexpr auto x<T*> = true;
}
template <typename T>
using pointer_type = val<dpointer_type::x<remove_cv<T>>>;