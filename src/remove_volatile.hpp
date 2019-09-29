#pragma once
#include "remove_type.hpp"
#include "make_volatile.hpp"
template <typename T>
using remove_volatile = remove_type<make_volatile, T>;