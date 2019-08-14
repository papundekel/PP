#pragma once
#include "remove_const.hpp"
#include "remove_volatile.hpp"

template <typename T>
using remove_cv = remove_volatile<remove_const<T>>;