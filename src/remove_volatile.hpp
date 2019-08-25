#pragma once
#include "type_t.hpp"
namespace dremove_volatile
{
    template <typename T>
    struct x : type_t<T> {};
    template <typename T>
    struct x<volatile T> : type_t<T> {};
}
template <typename T>
using remove_volatile = dremove_volatile::x<T>::t;