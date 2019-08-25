#pragma once
#include "is_template_nontype.hpp"
template <typename T>
requires is_template_nontype<value_t>::type<T>::v
using NOT = value_t<!T::v>;

template <typename... T>
requires (is_template_nontype<value_t>::type<T>::v && ...)
using AND = value_t<(T::v && ...)>;

template <typename... T>
requires (is_template_nontype<value_t>::type<T>::v && ...)
using OR = value_t<(T::v || ...)>;