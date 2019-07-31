#pragma once
#include "type_t.hpp"
#include "add_const.hpp"
#include "add_volatile.hpp"

template <typename T>
using add_cv_t = add_const_t<add_volatile_t<T>>;
template <typename T>
struct add_cv : type_t<add_cv_t> {};