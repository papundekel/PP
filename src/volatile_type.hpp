#pragma once
#include "same.hpp"
#include "make_volatile.hpp"
template <typename T>
using volatile_type = same<T, make_volatile<T>>;