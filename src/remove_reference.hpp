#pragma once
#include "type_t.hpp"
namespace dremove_reference
{
    template <typename T>
    struct x : type_t<T> {};
    template <typename T>
    struct x<T&> : type_t<T> {};
    template <typename T>
    struct x<T&&> : type_t<T> {};
}

template <typename T>
using remove_reference = dremove_reference::x<T>::t;