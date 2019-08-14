#pragma once
#include "type_t.hpp"
namespace detail
{
    template <typename T>
    struct remove_const : type_t<T> {};
    template <typename T>
    struct remove_const<const T> : type_t<T> {};
}
template <typename T>
using remove_const = detail::remove_const<T>::t;