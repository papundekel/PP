#pragma once
#include "type_t.hpp"
namespace detail
{
    template <typename T>
    struct remove_reference : type_t<T> {};
    template <typename T>
    struct remove_reference<T&> : type_t<T> {};
    template <typename T>
    struct remove_reference<T&&> : type_t<T> {};
}

template <typename T>
using remove_reference = detail::remove_reference<T>::type;