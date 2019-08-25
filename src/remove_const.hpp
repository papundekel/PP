#pragma once
#include "type_t.hpp"
namespace dremove_const
{
    template <typename T>
    struct x : type_t<T> {};
    template <typename T>
    struct x<const T> : type_t<T> {};
}
template <typename T>
using remove_const = dremove_const::x<T>::t;