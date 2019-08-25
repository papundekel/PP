#pragma once
#include "make_const.hpp"
#include "make_volatile.hpp"
template <typename T>
using make_cv = make_const<make_volatile<T>>;