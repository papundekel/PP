#pragma once
#include "is_template_nontype.hpp"

template <typename T>
requires is_template_nontype<val>::type<T>::v
using NOT = val<!T::v>;

template <typename... T>
requires (is_template_nontype<val>::type<T>::v && ...)
using AND = val<(T::v && ...)>;

template <typename... T>
requires (is_template_nontype<val>::type<T>::v && ...)
using OR = val<(T::v || ...)>;

template <typename... T>
requires (is_template_nontype<val>::type<T>::v && ...)
using ADD = val<(T::v + ...)>;

template <typename... T>
requires (is_template_nontype<val>::type<T>::v && ...)
using EQUAL = val<(T::v == ...)>;

template <typename T, typename U>
using IMPLY = OR<NOT<T>, U>;