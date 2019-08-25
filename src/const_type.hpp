#pragma once
#include "same.hpp"
#include "make_const.hpp"
template <typename T>
using const_type = same<T, make_const<T>>;