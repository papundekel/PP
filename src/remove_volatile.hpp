#pragma once
#include "type_t.hpp"
namespace detail
{
    template <typename T>
    struct remove_volatile : type_t<T> {};
    template <typename T>
    struct remove_volatile<volatile T> : type_t<T> {};
}
template <typename T>
using remove_volatile = detail::remove_volatile<T>::t;